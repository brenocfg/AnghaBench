#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct xcbc_state {scalar_t__ state; } ;
struct shash_desc {TYPE_1__* tfm; } ;
struct nx_sg {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  key; } ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {TYPE_3__ aes_xcbc; TYPE_2__ hdr; } ;
struct nx_csbcpb {TYPE_4__ cpb; } ;
struct TYPE_16__ {int outlen; } ;
struct TYPE_13__ {struct xcbc_state* key; } ;
struct TYPE_14__ {TYPE_5__ xcbc; } ;
struct nx_crypto_ctx {struct nx_sg* out_sg; TYPE_8__ op; TYPE_7__* ap; TYPE_6__ priv; struct nx_csbcpb* csbcpb; } ;
struct TYPE_15__ {int /*<<< orphan*/  sglen; } ;
struct TYPE_9__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  HCOP_FC_AES ; 
 int /*<<< orphan*/  NX_CPB_SET_KEY_SIZE (struct nx_csbcpb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_KS_AES_128 ; 
 int /*<<< orphan*/  NX_MODE_AES_XCBC_MAC ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct xcbc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xcbc_state*,int /*<<< orphan*/ ,int) ; 
 struct nx_sg* nx_build_sg_list (struct nx_sg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nx_ctx_init (struct nx_crypto_ctx*,int /*<<< orphan*/ ) ; 
 struct xcbc_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int nx_xcbc_init(struct shash_desc *desc)
{
	struct xcbc_state *sctx = shash_desc_ctx(desc);
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(&desc->tfm->base);
	struct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	struct nx_sg *out_sg;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	memset(sctx, 0, sizeof *sctx);

	NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
	csbcpb->cpb.hdr.mode = NX_MODE_AES_XCBC_MAC;

	memcpy(csbcpb->cpb.aes_xcbc.key, nx_ctx->priv.xcbc.key, AES_BLOCK_SIZE);
	memset(nx_ctx->priv.xcbc.key, 0, sizeof *nx_ctx->priv.xcbc.key);

	out_sg = nx_build_sg_list(nx_ctx->out_sg, (u8 *)sctx->state,
				  AES_BLOCK_SIZE, nx_ctx->ap->sglen);
	nx_ctx->op.outlen = (nx_ctx->out_sg - out_sg) * sizeof(struct nx_sg);

	return 0;
}