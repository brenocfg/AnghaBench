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
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int dummy; } ;

/* Variables and functions */
 struct crypto_aes_ctx* aes_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aesni_enc (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_aes_encrypt_x86 (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  irq_fpu_usable () ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

__attribute__((used)) static void aes_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct crypto_aes_ctx *ctx = aes_ctx(crypto_tfm_ctx(tfm));

	if (!irq_fpu_usable())
		crypto_aes_encrypt_x86(ctx, dst, src);
	else {
		kernel_fpu_begin();
		aesni_enc(ctx, dst, src);
		kernel_fpu_end();
	}
}