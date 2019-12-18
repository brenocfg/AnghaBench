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
struct shash_desc {int dummy; } ;
struct sha512_state {int* count; int* state; } ;
typedef  int /*<<< orphan*/  bits ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (struct sha512_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha512_update (struct shash_desc*,int const*,int) ; 
 struct sha512_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int
sha512_final(struct shash_desc *desc, u8 *hash)
{
	struct sha512_state *sctx = shash_desc_ctx(desc);
        static u8 padding[128] = { 0x80, };
	__be64 *dst = (__be64 *)hash;
	__be64 bits[2];
	unsigned int index, pad_len;
	int i;

	/* Save number of bits */
	bits[1] = cpu_to_be64(sctx->count[0] << 3);
	bits[0] = cpu_to_be64(sctx->count[1] << 3 | sctx->count[0] >> 61);

	/* Pad out to 112 mod 128. */
	index = sctx->count[0] & 0x7f;
	pad_len = (index < 112) ? (112 - index) : ((128+112) - index);
	sha512_update(desc, padding, pad_len);

	/* Append length (before padding) */
	sha512_update(desc, (const u8 *)bits, sizeof(bits));

	/* Store state in digest */
	for (i = 0; i < 8; i++)
		dst[i] = cpu_to_be64(sctx->state[i]);

	/* Zeroize sensitive information. */
	memset(sctx, 0, sizeof(struct sha512_state));

	return 0;
}