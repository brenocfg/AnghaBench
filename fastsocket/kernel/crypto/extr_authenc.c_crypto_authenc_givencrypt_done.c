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
struct skcipher_givcrypt_request {int /*<<< orphan*/  giv; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 struct skcipher_givcrypt_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  authenc_request_complete (struct aead_request*,int) ; 
 int crypto_authenc_genicv (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto_authenc_givencrypt_done(struct crypto_async_request *req,
					   int err)
{
	struct aead_request *areq = req->data;

	if (!err) {
		struct skcipher_givcrypt_request *greq = aead_request_ctx(areq);

		err = crypto_authenc_genicv(areq, greq->giv, 0);
	}

	authenc_request_complete(areq, err);
}