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
struct ahash_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int crypto_ahash_op (struct ahash_request*,int /*<<< orphan*/ ) ; 
 TYPE_1__* crypto_ahash_reqtfm (struct ahash_request*) ; 

int crypto_ahash_digest(struct ahash_request *req)
{
	return crypto_ahash_op(req, crypto_ahash_reqtfm(req)->digest);
}