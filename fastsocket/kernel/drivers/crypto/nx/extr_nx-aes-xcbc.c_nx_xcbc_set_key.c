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
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {TYPE_1__ xcbc; } ;
struct nx_crypto_ctx {TYPE_2__ priv; int /*<<< orphan*/ * props; int /*<<< orphan*/ * ap; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 128 
 int EINVAL ; 
 size_t NX_PROPS_AES_128 ; 
 struct nx_crypto_ctx* crypto_shash_ctx (struct crypto_shash*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int nx_xcbc_set_key(struct crypto_shash *desc,
			   const u8            *in_key,
			   unsigned int         key_len)
{
	struct nx_crypto_ctx *nx_ctx = crypto_shash_ctx(desc);

	switch (key_len) {
	case AES_KEYSIZE_128:
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		break;
	default:
		return -EINVAL;
	}

	memcpy(nx_ctx->priv.xcbc.key, in_key, key_len);

	return 0;
}