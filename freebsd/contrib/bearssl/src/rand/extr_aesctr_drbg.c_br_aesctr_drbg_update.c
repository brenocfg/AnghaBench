#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* vtable; } ;
struct TYPE_10__ {scalar_t__ cc; TYPE_1__ sk; } ;
typedef  TYPE_2__ br_aesctr_drbg_context ;
struct TYPE_11__ {int /*<<< orphan*/  (* init ) (TYPE_3__**,unsigned char*,int) ;int /*<<< orphan*/  (* run ) (TYPE_3__**,unsigned char*,int,unsigned char*,int) ;} ;

/* Variables and functions */
 int br_dec32be (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**,unsigned char*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__**,unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__**,unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__**,unsigned char*,int) ; 

void
br_aesctr_drbg_update(br_aesctr_drbg_context *ctx, const void *seed, size_t len)
{
	/*
	 * We use a Hirose construction on AES-256 to make a hash function.
	 * Function definition:
	 *  - running state consists in two 16-byte blocks G and H
	 *  - initial values of G and H are conventional
	 *  - there is a fixed block-sized constant C
	 *  - for next data block m:
	 *      set AES key to H||m
	 *      G' = E(G) xor G
	 *      H' = E(G xor C) xor G xor C
	 *      G <- G', H <- H'
	 *  - once all blocks have been processed, output is H||G
	 *
	 * Constants:
	 *   G_init = B6 B6 ... B6
	 *   H_init = A5 A5 ... A5
	 *   C      = 01 00 ... 00
	 *
	 * With this hash function h(), we compute the new state as
	 * follows:
	 *  - produce a state-dependent value s as encryption of an
	 *    all-one block with AES and the current key
	 *  - compute the new key as the first 128 bits of h(s||seed)
	 *
	 * Original Hirose article:
	 *    https://www.iacr.org/archive/fse2006/40470213/40470213.pdf
	 */

	unsigned char s[16], iv[12];
	unsigned char G[16], H[16];
	int first;

	/*
	 * Use an all-one IV to get a fresh output block that depends on the
	 * current seed.
	 */
	memset(iv, 0xFF, sizeof iv);
	memset(s, 0, 16);
	ctx->sk.vtable->run(&ctx->sk.vtable, iv, 0xFFFFFFFF, s, 16);

	/*
	 * Set G[] and H[] to conventional start values.
	 */
	memset(G, 0xB6, sizeof G);
	memset(H, 0x5A, sizeof H);

	/*
	 * Process the concatenation of the current state and the seed
	 * with the custom hash function.
	 */
	first = 1;
	for (;;) {
		unsigned char tmp[32];
		unsigned char newG[16];

		/*
		 * Assemble new key H||m into tmp[].
		 */
		memcpy(tmp, H, 16);
		if (first) {
			memcpy(tmp + 16, s, 16);
			first = 0;
		} else {
			size_t clen;

			if (len == 0) {
				break;
			}
			clen = len < 16 ? len : 16;
			memcpy(tmp + 16, seed, clen);
			memset(tmp + 16 + clen, 0, 16 - clen);
			seed = (const unsigned char *)seed + clen;
			len -= clen;
		}
		ctx->sk.vtable->init(&ctx->sk.vtable, tmp, 32);

		/*
		 * Compute new G and H values.
		 */
		memcpy(iv, G, 12);
		memcpy(newG, G, 16);
		ctx->sk.vtable->run(&ctx->sk.vtable, iv,
			br_dec32be(G + 12), newG, 16);
		iv[0] ^= 0x01;
		memcpy(H, G, 16);
		H[0] ^= 0x01;
		ctx->sk.vtable->run(&ctx->sk.vtable, iv,
			br_dec32be(G + 12), H, 16);
		memcpy(G, newG, 16);
	}

	/*
	 * Output hash value is H||G. We truncate it to its first 128 bits,
	 * i.e. H; that's our new AES key.
	 */
	ctx->sk.vtable->init(&ctx->sk.vtable, H, 16);
	ctx->cc = 0;
}