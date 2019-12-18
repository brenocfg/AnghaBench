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
struct crypto_ablkcipher {int dummy; } ;
struct cryptd_queue {int dummy; } ;
struct cryptd_blkcipher_request_ctx {int /*<<< orphan*/  complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct ablkcipher_request {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 struct cryptd_blkcipher_request_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int cryptd_enqueue_request (struct cryptd_queue*,TYPE_1__*) ; 
 struct cryptd_queue* cryptd_get_queue (int /*<<< orphan*/ ) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 

__attribute__((used)) static int cryptd_blkcipher_enqueue(struct ablkcipher_request *req,
				    crypto_completion_t complete)
{
	struct cryptd_blkcipher_request_ctx *rctx = ablkcipher_request_ctx(req);
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct cryptd_queue *queue;

	queue = cryptd_get_queue(crypto_ablkcipher_tfm(tfm));
	rctx->complete = req->base.complete;
	req->base.complete = complete;

	return cryptd_enqueue_request(queue, &req->base);
}