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
struct crypto_async_request {struct ahash_request* data; } ;
struct ahash_request_priv {void* data; int /*<<< orphan*/  (* complete ) (void*,int) ;} ;
struct ahash_request {struct ahash_request_priv* priv; } ;
typedef  int /*<<< orphan*/  (* crypto_completion_t ) (void*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_op_unaligned_finish (struct ahash_request*,int) ; 

__attribute__((used)) static void ahash_op_unaligned_done(struct crypto_async_request *req, int err)
{
	struct ahash_request *areq = req->data;
	struct ahash_request_priv *priv = areq->priv;
	crypto_completion_t complete = priv->complete;
	void *data = priv->data;

	ahash_op_unaligned_finish(areq, err);

	complete(data, err);
}