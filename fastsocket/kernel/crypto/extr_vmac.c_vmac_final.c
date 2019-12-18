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
typedef  int /*<<< orphan*/  vmac_t ;
typedef  int /*<<< orphan*/  u8 ;
struct vmac_ctx_t {int /*<<< orphan*/  __vmac_ctx; } ;
struct vmac_ctx {int dummy; } ;
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 struct vmac_ctx_t* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmac (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vmac_ctx_t*) ; 

__attribute__((used)) static int vmac_final(struct shash_desc *pdesc, u8 *out)
{
	struct crypto_shash *parent = pdesc->tfm;
	struct vmac_ctx_t *ctx = crypto_shash_ctx(parent);
	vmac_t mac;
	u8 nonce[16] = {};

	mac = vmac(NULL, 0, nonce, NULL, ctx);
	memcpy(out, &mac, sizeof(vmac_t));
	memset(&mac, 0, sizeof(vmac_t));
	memset(&ctx->__vmac_ctx, 0, sizeof(struct vmac_ctx));
	return 0;
}