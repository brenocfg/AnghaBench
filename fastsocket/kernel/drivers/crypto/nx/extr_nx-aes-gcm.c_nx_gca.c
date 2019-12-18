#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scatter_walk {int dummy; } ;
struct nx_sg {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  out_pat; } ;
struct TYPE_11__ {TYPE_4__ aes_gca; } ;
struct nx_csbcpb {TYPE_5__ cpb; } ;
struct TYPE_12__ {int inlen; } ;
struct nx_crypto_ctx {TYPE_3__* stats; TYPE_6__ op_aead; struct nx_sg* in_sg; TYPE_1__* ap; struct nx_csbcpb* csbcpb_aead; } ;
struct TYPE_8__ {int flags; } ;
struct aead_request {int /*<<< orphan*/  assoclen; TYPE_2__ base; int /*<<< orphan*/  assoc; } ;
struct TYPE_9__ {int /*<<< orphan*/  aes_bytes; int /*<<< orphan*/  aes_ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  sglen; int /*<<< orphan*/  databytelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int /*<<< orphan*/  SCATTERWALK_FROM_SG ; 
 int /*<<< orphan*/  atomic64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nx_hcall_sync (struct nx_crypto_ctx*,TYPE_6__*,int) ; 
 struct nx_sg* nx_walk_and_build (struct nx_sg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ *,struct scatter_walk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nx_gca(struct nx_crypto_ctx  *nx_ctx,
		  struct aead_request   *req,
		  u8                    *out)
{
	struct nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;
	int rc = -EINVAL;
	struct scatter_walk walk;
	struct nx_sg *nx_sg = nx_ctx->in_sg;

	if (req->assoclen > nx_ctx->ap->databytelen)
		goto out;

	if (req->assoclen <= AES_BLOCK_SIZE) {
		scatterwalk_start(&walk, req->assoc);
		scatterwalk_copychunks(out, &walk, req->assoclen,
				       SCATTERWALK_FROM_SG);
		scatterwalk_done(&walk, SCATTERWALK_FROM_SG, 0);

		rc = 0;
		goto out;
	}

	nx_sg = nx_walk_and_build(nx_sg, nx_ctx->ap->sglen, req->assoc, 0,
				  req->assoclen);
	nx_ctx->op_aead.inlen = (nx_ctx->in_sg - nx_sg) * sizeof(struct nx_sg);

	rc = nx_hcall_sync(nx_ctx, &nx_ctx->op_aead,
			   req->base.flags & CRYPTO_TFM_REQ_MAY_SLEEP);
	if (rc)
		goto out;

	atomic_inc(&(nx_ctx->stats->aes_ops));
	atomic64_add(req->assoclen, &(nx_ctx->stats->aes_bytes));

	memcpy(out, csbcpb_aead->cpb.aes_gca.out_pat, AES_BLOCK_SIZE);
out:
	return rc;
}