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
struct aead_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; scalar_t__ assoclen; } ;

/* Variables and functions */
 int aead_perform (struct aead_request*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_aead_ivsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 

__attribute__((used)) static int aead_decrypt(struct aead_request *req)
{
	unsigned ivsize = crypto_aead_ivsize(crypto_aead_reqtfm(req));
	return aead_perform(req, 0, req->assoclen + ivsize,
			req->cryptlen, req->iv);
}