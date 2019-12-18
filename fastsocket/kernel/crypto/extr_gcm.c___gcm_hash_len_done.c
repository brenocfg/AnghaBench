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
struct crypto_gcm_req_priv_ctx {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  __gcm_hash_final_done (struct aead_request*,int) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int gcm_hash_final (struct aead_request*,struct crypto_gcm_req_priv_ctx*) ; 

__attribute__((used)) static void __gcm_hash_len_done(struct aead_request *req, int err)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);

	if (!err) {
		err = gcm_hash_final(req, pctx);
		if (err == -EINPROGRESS || err == -EBUSY)
			return;
	}

	__gcm_hash_final_done(req, err);
}