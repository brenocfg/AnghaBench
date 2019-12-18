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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  encrypt_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bf_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	const __be32 *in_blk = (const __be32 *)src;
	__be32 *const out_blk = (__be32 *)dst;
	u32 in32[2], out32[2];

	in32[0] = be32_to_cpu(in_blk[0]);
	in32[1] = be32_to_cpu(in_blk[1]);
	encrypt_block(crypto_tfm_ctx(tfm), out32, in32);
	out_blk[0] = cpu_to_be32(out32[0]);
	out_blk[1] = cpu_to_be32(out32[1]);
}