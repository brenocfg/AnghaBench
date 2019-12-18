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
typedef  int u32 ;
struct shash_desc {int dummy; } ;
struct rmd128_ctx {int byte_count; int /*<<< orphan*/ * state; } ;
typedef  int /*<<< orphan*/  bits ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memset (struct rmd128_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rmd128_update (struct shash_desc*,int const*,int) ; 
 struct rmd128_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int rmd128_final(struct shash_desc *desc, u8 *out)
{
	struct rmd128_ctx *rctx = shash_desc_ctx(desc);
	u32 i, index, padlen;
	__le64 bits;
	__le32 *dst = (__le32 *)out;
	static const u8 padding[64] = { 0x80, };

	bits = cpu_to_le64(rctx->byte_count << 3);

	/* Pad out to 56 mod 64 */
	index = rctx->byte_count & 0x3f;
	padlen = (index < 56) ? (56 - index) : ((64+56) - index);
	rmd128_update(desc, padding, padlen);

	/* Append length */
	rmd128_update(desc, (const u8 *)&bits, sizeof(bits));

	/* Store state in digest */
	for (i = 0; i < 4; i++)
		dst[i] = cpu_to_le32p(&rctx->state[i]);

	/* Wipe context */
	memset(rctx, 0, sizeof(*rctx));

	return 0;
}