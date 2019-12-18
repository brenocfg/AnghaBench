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
struct crypto_gcm_setkey_result {int err; int /*<<< orphan*/  completion; } ;
struct crypto_async_request {struct crypto_gcm_setkey_result* data; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypto_gcm_setkey_done(struct crypto_async_request *req, int err)
{
	struct crypto_gcm_setkey_result *result = req->data;

	if (err == -EINPROGRESS)
		return;

	result->err = err;
	complete(&result->completion);
}