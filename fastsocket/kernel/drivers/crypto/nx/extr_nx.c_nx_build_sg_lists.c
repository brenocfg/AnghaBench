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
struct scatterlist {int dummy; } ;
struct nx_sg {int dummy; } ;
struct TYPE_4__ {int inlen; int outlen; } ;
struct nx_crypto_ctx {struct nx_sg* out_sg; TYPE_2__ op; struct nx_sg* in_sg; TYPE_1__* ap; } ;
struct blkcipher_desc {int /*<<< orphan*/  info; } ;
struct TYPE_3__ {int /*<<< orphan*/  sglen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nx_sg* nx_walk_and_build (struct nx_sg*,int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 

int nx_build_sg_lists(struct nx_crypto_ctx  *nx_ctx,
		      struct blkcipher_desc *desc,
		      struct scatterlist    *dst,
		      struct scatterlist    *src,
		      unsigned int           nbytes,
		      u8                    *iv)
{
	struct nx_sg *nx_insg = nx_ctx->in_sg;
	struct nx_sg *nx_outsg = nx_ctx->out_sg;

	if (iv)
		memcpy(iv, desc->info, AES_BLOCK_SIZE);

	nx_insg = nx_walk_and_build(nx_insg, nx_ctx->ap->sglen, src, 0, nbytes);
	nx_outsg = nx_walk_and_build(nx_outsg, nx_ctx->ap->sglen, dst, 0, nbytes);

	/* these lengths should be negative, which will indicate to phyp that
	 * the input and output parameters are scatterlists, not linear
	 * buffers */
	nx_ctx->op.inlen = (nx_ctx->in_sg - nx_insg) * sizeof(struct nx_sg);
	nx_ctx->op.outlen = (nx_ctx->out_sg - nx_outsg) * sizeof(struct nx_sg);

	return 0;
}