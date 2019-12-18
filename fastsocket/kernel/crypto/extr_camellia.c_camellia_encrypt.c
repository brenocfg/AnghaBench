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
struct camellia_ctx {int key_length; int /*<<< orphan*/  key_table; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  camellia_do_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct camellia_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void camellia_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	const struct camellia_ctx *cctx = crypto_tfm_ctx(tfm);
	const __be32 *src = (const __be32 *)in;
	__be32 *dst = (__be32 *)out;

	u32 tmp[4];

	tmp[0] = be32_to_cpu(src[0]);
	tmp[1] = be32_to_cpu(src[1]);
	tmp[2] = be32_to_cpu(src[2]);
	tmp[3] = be32_to_cpu(src[3]);

	camellia_do_encrypt(cctx->key_table, tmp,
		cctx->key_length == 16 ? 24 : 32 /* for key lengths of 24 and 32 */
	);

	/* do_encrypt returns 0,1 swapped with 2,3 */
	dst[0] = cpu_to_be32(tmp[2]);
	dst[1] = cpu_to_be32(tmp[3]);
	dst[2] = cpu_to_be32(tmp[0]);
	dst[3] = cpu_to_be32(tmp[1]);
}