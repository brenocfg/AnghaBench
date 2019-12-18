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
struct crypto_async_request {struct aead_request* data; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gcm_hash_crypt_done (struct aead_request*,int) ; 

__attribute__((used)) static void gcm_hash_crypt_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;

	__gcm_hash_crypt_done(req, err);
}