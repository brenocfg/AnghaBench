#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  complete; } ;
struct ahash_request {TYPE_1__ base; } ;
struct TYPE_4__ {int (* final ) (struct ahash_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  ahash_def_finup_done2 ; 
 int /*<<< orphan*/  ahash_def_finup_finish2 (struct ahash_request*,int) ; 
 TYPE_2__* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int stub1 (struct ahash_request*) ; 

__attribute__((used)) static int ahash_def_finup_finish1(struct ahash_request *req, int err)
{
	if (err)
		goto out;

	req->base.complete = ahash_def_finup_done2;
	req->base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	err = crypto_ahash_reqtfm(req)->final(req);

out:
	ahash_def_finup_finish2(req, err);
	return err;
}