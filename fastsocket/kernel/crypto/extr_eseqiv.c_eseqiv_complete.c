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
struct skcipher_givcrypt_request {int dummy; } ;
struct crypto_async_request {struct skcipher_givcrypt_request* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  eseqiv_complete2 (struct skcipher_givcrypt_request*) ; 
 int /*<<< orphan*/  skcipher_givcrypt_complete (struct skcipher_givcrypt_request*,int) ; 

__attribute__((used)) static void eseqiv_complete(struct crypto_async_request *base, int err)
{
	struct skcipher_givcrypt_request *req = base->data;

	if (err)
		goto out;

	eseqiv_complete2(req);

out:
	skcipher_givcrypt_complete(req, err);
}