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
struct crypto_async_request {struct aead_givcrypt_request* data; } ;
struct aead_givcrypt_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_givcrypt_complete (struct aead_givcrypt_request*,int) ; 
 int /*<<< orphan*/  seqiv_aead_complete2 (struct aead_givcrypt_request*,int) ; 

__attribute__((used)) static void seqiv_aead_complete(struct crypto_async_request *base, int err)
{
	struct aead_givcrypt_request *req = base->data;

	seqiv_aead_complete2(req, err);
	aead_givcrypt_complete(req, err);
}