#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct secasindex {scalar_t__ proto; } ;
struct sadb_spirange {int sadb_spirange_min; int sadb_spirange_max; } ;
struct TYPE_2__ {int getspi_count; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_IPCOMP ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * key_checkspidup (struct secasindex*,int) ; 
 int key_random () ; 
 int key_spi_maxval ; 
 int key_spi_minval ; 
 int key_spi_trycnt ; 
 TYPE_1__ keystat ; 
 int /*<<< orphan*/  sadb_mutex ; 

__attribute__((used)) static u_int32_t
key_do_getnewspi(
				 struct sadb_spirange *spirange,
				 struct secasindex *saidx)
{
	u_int32_t newspi;
	u_int32_t keymin, keymax;
	int count = key_spi_trycnt;
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	
	/* set spi range to allocate */
	if (spirange != NULL) {
		keymin = spirange->sadb_spirange_min;
		keymax = spirange->sadb_spirange_max;
	} else {
		keymin = key_spi_minval;
		keymax = key_spi_maxval;
	}
	/* IPCOMP needs 2-byte SPI */
	if (saidx->proto == IPPROTO_IPCOMP) {
		u_int32_t t;
		if (keymin >= 0x10000)
			keymin = 0xffff;
		if (keymax >= 0x10000)
			keymax = 0xffff;
		if (keymin > keymax) {
			t = keymin; keymin = keymax; keymax = t;
		}
	}
	
	if (keymin == keymax) {
		if (key_checkspidup(saidx, keymin) != NULL) {
			ipseclog((LOG_DEBUG, "key_do_getnewspi: SPI %u exists already.\n", keymin));
			return 0;
		}
		
		count--; /* taking one cost. */
		newspi = keymin;
		
	} else {
		
		u_int32_t range = keymax - keymin + 1;  /* overflow value of zero means full range */
		
		/* init SPI */
		newspi = 0;
		
		/* when requesting to allocate spi ranged */
		while (count--) {
			u_int32_t rand_val = key_random();
			
			/* generate pseudo-random SPI value ranged. */
			newspi = (range == 0 ? rand_val : keymin + (rand_val % range));
			
			if (key_checkspidup(saidx, newspi) == NULL)
				break;
		}
		
		if (count == 0 || newspi == 0) {
			ipseclog((LOG_DEBUG, "key_do_getnewspi: to allocate spi is failed.\n"));
			return 0;
		}
	}
	
	/* statistics */
	keystat.getspi_count =
	(keystat.getspi_count + key_spi_trycnt - count) / 2;
	
	return newspi;
}