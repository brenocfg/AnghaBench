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
 int /*<<< orphan*/  seqiv_complete2 (struct skcipher_givcrypt_request*,int) ; 
 int /*<<< orphan*/  skcipher_givcrypt_complete (struct skcipher_givcrypt_request*,int) ; 

__attribute__((used)) static void seqiv_complete(struct crypto_async_request *base, int err)
{
	struct skcipher_givcrypt_request *req = base->data;

	seqiv_complete2(req, err);
	skcipher_givcrypt_complete(req, err);
}