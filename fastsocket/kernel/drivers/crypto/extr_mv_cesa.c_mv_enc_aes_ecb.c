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
struct mv_req_ctx {scalar_t__ decrypt; int /*<<< orphan*/  op; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COP_AES_ECB ; 
 struct mv_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int mv_handle_req (struct ablkcipher_request*) ; 

__attribute__((used)) static int mv_enc_aes_ecb(struct ablkcipher_request *req)
{
	struct mv_req_ctx *req_ctx = ablkcipher_request_ctx(req);

	req_ctx->op = COP_AES_ECB;
	req_ctx->decrypt = 0;

	return mv_handle_req(req);
}