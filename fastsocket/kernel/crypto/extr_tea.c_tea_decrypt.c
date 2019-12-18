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
typedef  int u32 ;
struct tea_ctx {int* KEY; } ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int TEA_DELTA ; 
 int TEA_ROUNDS ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct tea_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void tea_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	u32 y, z, n, sum;
	u32 k0, k1, k2, k3;
	struct tea_ctx *ctx = crypto_tfm_ctx(tfm);
	const __le32 *in = (const __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	k0 = ctx->KEY[0];
	k1 = ctx->KEY[1];
	k2 = ctx->KEY[2];
	k3 = ctx->KEY[3];

	sum = TEA_DELTA << 5;

	n = TEA_ROUNDS;

	while (n-- > 0) {
		z -= ((y << 4) + k2) ^ (y + sum) ^ ((y >> 5) + k3);
		y -= ((z << 4) + k0) ^ (z + sum) ^ ((z >> 5) + k1);
		sum -= TEA_DELTA;
	}
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
}