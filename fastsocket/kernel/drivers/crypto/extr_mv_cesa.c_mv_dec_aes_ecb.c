#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mv_req_ctx {int decrypt; int /*<<< orphan*/  op; } ;
struct mv_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  COP_AES_ECB ; 
 struct mv_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  compute_aes_dec_key (struct mv_ctx*) ; 
 struct mv_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int mv_handle_req (struct ablkcipher_request*) ; 

__attribute__((used)) static int mv_dec_aes_ecb(struct ablkcipher_request *req)
{
	struct mv_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct mv_req_ctx *req_ctx = ablkcipher_request_ctx(req);

	req_ctx->op = COP_AES_ECB;
	req_ctx->decrypt = 1;

	compute_aes_dec_key(ctx);
	return mv_handle_req(req);
}