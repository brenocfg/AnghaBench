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
struct skcipher_givcrypt_request {int /*<<< orphan*/  creq; } ;

/* Variables and functions */
 int crypto_ablkcipher_decrypt (int /*<<< orphan*/ *) ; 

int skcipher_null_givdecrypt(struct skcipher_givcrypt_request *req)
{
	return crypto_ablkcipher_decrypt(&req->creq);
}