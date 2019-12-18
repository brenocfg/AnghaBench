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
struct mv_req_ctx {scalar_t__ op; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;
struct TYPE_2__ {scalar_t__ sram; struct ablkcipher_request* cur_req; } ;

/* Variables and functions */
 scalar_t__ COP_AES_CBC ; 
 scalar_t__ SRAM_DATA_IV_BUF ; 
 struct mv_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 TYPE_1__* cpg ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void mv_crypto_algo_completion(void)
{
	struct ablkcipher_request *req = cpg->cur_req;
	struct mv_req_ctx *req_ctx = ablkcipher_request_ctx(req);

	if (req_ctx->op != COP_AES_CBC)
		return ;

	memcpy(req->info, cpg->sram + SRAM_DATA_IV_BUF, 16);
}