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
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  iv; } ;
struct TYPE_2__ {int /*<<< orphan*/  iv; } ;
struct aead_givcrypt_request {TYPE_1__ areq; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 struct aead_request* aead_givcrypt_reqctx (struct aead_givcrypt_request*) ; 
 struct crypto_aead* aead_givcrypt_reqtfm (struct aead_givcrypt_request*) ; 
 int /*<<< orphan*/  crypto_aead_ivsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seqiv_aead_complete2(struct aead_givcrypt_request *req, int err)
{
	struct aead_request *subreq = aead_givcrypt_reqctx(req);
	struct crypto_aead *geniv;

	if (err == -EINPROGRESS)
		return;

	if (err)
		goto out;

	geniv = aead_givcrypt_reqtfm(req);
	memcpy(req->areq.iv, subreq->iv, crypto_aead_ivsize(geniv));

out:
	kfree(subreq->iv);
}