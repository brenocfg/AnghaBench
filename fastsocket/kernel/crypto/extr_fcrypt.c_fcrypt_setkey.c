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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct fcrypt_ctx {void** sched; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 
 struct fcrypt_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ror56 (int,int,int) ; 
 int /*<<< orphan*/  ror56_64 (int,int) ; 

__attribute__((used)) static int fcrypt_setkey(struct crypto_tfm *tfm, const u8 *key, unsigned int keylen)
{
	struct fcrypt_ctx *ctx = crypto_tfm_ctx(tfm);

#if BITS_PER_LONG == 64  /* the 64-bit version can also be used for 32-bit
			  * kernels - it seems to be faster but the code is
			  * larger */

	u64 k;	/* k holds all 56 non-parity bits */

	/* discard the parity bits */
	k = (*key++) >> 1;
	k <<= 7;
	k |= (*key++) >> 1;
	k <<= 7;
	k |= (*key++) >> 1;
	k <<= 7;
	k |= (*key++) >> 1;
	k <<= 7;
	k |= (*key++) >> 1;
	k <<= 7;
	k |= (*key++) >> 1;
	k <<= 7;
	k |= (*key++) >> 1;
	k <<= 7;
	k |= (*key) >> 1;

	/* Use lower 32 bits for schedule, rotate by 11 each round (16 times) */
	ctx->sched[0x0] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x1] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x2] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x3] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x4] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x5] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x6] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x7] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x8] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0x9] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0xa] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0xb] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0xc] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0xd] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0xe] = cpu_to_be32(k); ror56_64(k, 11);
	ctx->sched[0xf] = cpu_to_be32(k);

	return 0;
#else
	u32 hi, lo;		/* hi is upper 24 bits and lo lower 32, total 56 */

	/* discard the parity bits */
	lo = (*key++) >> 1;
	lo <<= 7;
	lo |= (*key++) >> 1;
	lo <<= 7;
	lo |= (*key++) >> 1;
	lo <<= 7;
	lo |= (*key++) >> 1;
	hi = lo >> 4;
	lo &= 0xf;
	lo <<= 7;
	lo |= (*key++) >> 1;
	lo <<= 7;
	lo |= (*key++) >> 1;
	lo <<= 7;
	lo |= (*key++) >> 1;
	lo <<= 7;
	lo |= (*key) >> 1;

	/* Use lower 32 bits for schedule, rotate by 11 each round (16 times) */
	ctx->sched[0x0] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x1] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x2] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x3] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x4] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x5] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x6] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x7] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x8] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0x9] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0xa] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0xb] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0xc] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0xd] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0xe] = cpu_to_be32(lo); ror56(hi, lo, 11);
	ctx->sched[0xf] = cpu_to_be32(lo);
	return 0;
#endif
}