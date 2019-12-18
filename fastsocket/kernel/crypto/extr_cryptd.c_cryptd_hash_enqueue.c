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
struct crypto_ahash {int dummy; } ;
struct cryptd_queue {int dummy; } ;
struct cryptd_hash_request_ctx {int /*<<< orphan*/  complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct ahash_request {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  crypto_completion_t ;

/* Variables and functions */
 struct cryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int cryptd_enqueue_request (struct cryptd_queue*,TYPE_1__*) ; 
 struct cryptd_queue* cryptd_get_queue (int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 

__attribute__((used)) static int cryptd_hash_enqueue(struct ahash_request *req,
				crypto_completion_t complete)
{
	struct cryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct cryptd_queue *queue =
		cryptd_get_queue(crypto_ahash_tfm(tfm));

	rctx->complete = req->base.complete;
	req->base.complete = complete;

	return cryptd_enqueue_request(queue, &req->base);
}