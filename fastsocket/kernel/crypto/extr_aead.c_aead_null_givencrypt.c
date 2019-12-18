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
struct aead_givcrypt_request {int /*<<< orphan*/  areq; } ;

/* Variables and functions */
 int crypto_aead_encrypt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aead_null_givencrypt(struct aead_givcrypt_request *req)
{
	return crypto_aead_encrypt(&req->areq);
}