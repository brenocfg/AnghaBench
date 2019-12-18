#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  nonce; } ;
struct TYPE_4__ {TYPE_1__ ccm; } ;
struct nx_crypto_ctx {TYPE_2__ priv; } ;
struct crypto_aead {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ccm_aes_nx_set_key (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int ccm4309_aes_nx_set_key(struct crypto_aead *tfm,
				  const u8           *in_key,
				  unsigned int        key_len)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&tfm->base);

	if (key_len < 3)
		return -EINVAL;

	key_len -= 3;

	memcpy(nx_ctx->priv.ccm.nonce, in_key + key_len, 3);

	return ccm_aes_nx_set_key(tfm, in_key, key_len);
}