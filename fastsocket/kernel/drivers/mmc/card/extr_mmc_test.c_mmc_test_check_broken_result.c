#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_test_card {int dummy; } ;
struct mmc_request {TYPE_3__* data; TYPE_2__* stop; TYPE_1__* cmd; } ;
struct TYPE_6__ {int error; int blocks; scalar_t__ bytes_xfered; scalar_t__ blksz; } ;
struct TYPE_5__ {int error; } ;
struct TYPE_4__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int RESULT_FAIL ; 
 int RESULT_UNSUP_HOST ; 

__attribute__((used)) static int mmc_test_check_broken_result(struct mmc_test_card *test,
	struct mmc_request *mrq)
{
	int ret;

	BUG_ON(!mrq || !mrq->cmd || !mrq->data);

	ret = 0;

	if (!ret && mrq->cmd->error)
		ret = mrq->cmd->error;
	if (!ret && mrq->data->error == 0)
		ret = RESULT_FAIL;
	if (!ret && mrq->data->error != -ETIMEDOUT)
		ret = mrq->data->error;
	if (!ret && mrq->stop && mrq->stop->error)
		ret = mrq->stop->error;
	if (mrq->data->blocks > 1) {
		if (!ret && mrq->data->bytes_xfered > mrq->data->blksz)
			ret = RESULT_FAIL;
	} else {
		if (!ret && mrq->data->bytes_xfered > 0)
			ret = RESULT_FAIL;
	}

	if (ret == -EINVAL)
		ret = RESULT_UNSUP_HOST;

	return ret;
}