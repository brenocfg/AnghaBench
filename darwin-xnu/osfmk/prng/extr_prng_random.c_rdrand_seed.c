#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct ccdigest_info {int dummy; } ;

/* Variables and functions */
 int CCSHA256_OUTPUT_SIZE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ccdigest_di_clear (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdigest_di_decl (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdigest_final (struct ccdigest_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdigest_init (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdigest_update (struct ccdigest_info const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct ccdigest_info ccsha256_ltc_di ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rdrand_retry (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static size_t
rdrand_seed(void * buf, size_t nwords)
{
	size_t i;
	uint64_t w;
	uint8_t hash[CCSHA256_OUTPUT_SIZE];
	const struct ccdigest_info * di = &ccsha256_ltc_di;

	ccdigest_di_decl(di, ctx);
	ccdigest_init(di, ctx);

	for (i = 0; i < 1023; i += 1) {
		if (!rdrand_retry(&w, 10)) {
			nwords = 0;
			goto out;
		}
		ccdigest_update(di, ctx, sizeof w, &w);
	}

	ccdigest_final(di, ctx, hash);

	if (nwords > 2) {
		nwords = 2;
	}

	memcpy(buf, hash, nwords * sizeof(uint64_t));

out:
	ccdigest_di_clear(di, ctx);
	bzero(hash, sizeof hash);
	bzero(&w, sizeof w);

	return nwords;
}