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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct shash_desc {int dummy; } ;
struct ksign_public_key {int version; int timestamp; long expiredate; int /*<<< orphan*/ * pkey; } ;

/* Variables and functions */
 int DSA_NPKEY ; 
 unsigned int PUBKEY_ALGO_DSA ; 
 int /*<<< orphan*/  SHA1_putc (struct shash_desc*,unsigned int) ; 
 int /*<<< orphan*/  SHA1_write (struct shash_desc*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpi_get_buffer (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 
 unsigned int mpi_get_nbits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksign_calc_pk_keyid(struct shash_desc *digest,
				struct ksign_public_key *pk)
{
	unsigned n;
	unsigned nb[DSA_NPKEY];
	unsigned nn[DSA_NPKEY];
	uint8_t *pp[DSA_NPKEY];
	uint32_t a32;
	int i;
	int npkey = DSA_NPKEY;

	n = pk->version < 4 ? 8 : 6;
	for (i = 0; i < npkey; i++) {
		nb[i] = mpi_get_nbits(pk->pkey[i]);
		pp[i] = mpi_get_buffer( pk->pkey[i], nn + i, NULL);
		n += 2 + nn[i];
	}

	SHA1_putc(digest, 0x99);     /* ctb */
	SHA1_putc(digest, n >> 8);   /* 2 uint8_t length header */
	SHA1_putc(digest, n);

	if (pk->version < 4)
		SHA1_putc(digest, 3);
	else
		SHA1_putc(digest, 4);

	a32 = pk->timestamp;
	SHA1_putc(digest, a32 >> 24 );
	SHA1_putc(digest, a32 >> 16 );
	SHA1_putc(digest, a32 >>  8 );
	SHA1_putc(digest, a32 >>  0 );

	if (pk->version < 4) {
		uint16_t a16;

		if( pk->expiredate )
			a16 = (uint16_t)
				((pk->expiredate - pk->timestamp) / 86400L);
		else
			a16 = 0;
		SHA1_putc(digest, a16 >> 8);
		SHA1_putc(digest, a16 >> 0);
	}

	SHA1_putc(digest, PUBKEY_ALGO_DSA);

	for (i = 0; i < npkey; i++) {
		SHA1_putc(digest, nb[i] >> 8);
		SHA1_putc(digest, nb[i]);
		SHA1_write(digest, pp[i], nn[i]);
		kfree(pp[i]);
	}
}