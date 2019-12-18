#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct TYPE_8__ {TYPE_3__ aes_cca; TYPE_2__ hdr; TYPE_1__ aes_ccm; } ;
struct nx_csbcpb {TYPE_4__ cpb; } ;
struct nx_crypto_ctx {int /*<<< orphan*/ * props; int /*<<< orphan*/ * ap; struct nx_csbcpb* csbcpb_aead; struct nx_csbcpb* csbcpb; } ;
struct crypto_aead {int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 128 
 int EINVAL ; 
 int /*<<< orphan*/  HCOP_FC_AES ; 
 int /*<<< orphan*/  NX_CPB_SET_KEY_SIZE (struct nx_csbcpb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_KS_AES_128 ; 
 int /*<<< orphan*/  NX_MODE_AES_CCA ; 
 int /*<<< orphan*/  NX_MODE_AES_CCM ; 
 size_t NX_PROPS_AES_128 ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  nx_ctx_init (struct nx_crypto_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccm_aes_nx_set_key(struct crypto_aead *tfm,
			      const u8           *in_key,
			      unsigned int        key_len)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&tfm->base);
	struct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	struct nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	switch (key_len) {
	case AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->props[NX_PROPS_AES_128];
		break;
	default:
		return -EINVAL;
	}

	csbcpb->cpb.hdr.mode = NX_MODE_AES_CCM;
	memcpy(csbcpb->cpb.aes_ccm.key, in_key, key_len);

	csbcpb_aead->cpb.hdr.mode = NX_MODE_AES_CCA;
	memcpy(csbcpb_aead->cpb.aes_cca.key, in_key, key_len);

	return 0;

}