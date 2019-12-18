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
 int XTEA_DELTA ; 
 int XTEA_ROUNDS ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct tea_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void xtea_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	u32 y, z, sum;
	struct tea_ctx *ctx = crypto_tfm_ctx(tfm);
	const __le32 *in = (const __le32 *)src;
	__le32 *out = (__le32 *)dst;

	y = le32_to_cpu(in[0]);
	z = le32_to_cpu(in[1]);

	sum = XTEA_DELTA * XTEA_ROUNDS;

	while (sum) {
		z -= ((y << 4 ^ y >> 5) + y) ^ (sum + ctx->KEY[sum>>11 & 3]);
		sum -= XTEA_DELTA;
		y -= ((z << 4 ^ z >> 5) + z) ^ (sum + ctx->KEY[sum & 3]);
	}
	
	out[0] = cpu_to_le32(y);
	out[1] = cpu_to_le32(z);
}