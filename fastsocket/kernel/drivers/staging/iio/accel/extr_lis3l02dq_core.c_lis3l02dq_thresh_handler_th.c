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
struct TYPE_2__ {int /*<<< orphan*/  ws; } ;
struct lis3l02dq_state {TYPE_1__ work_cont_thresh; int /*<<< orphan*/  last_timestamp; } ;
struct iio_dev {struct lis3l02dq_state* dev_data; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lis3l02dq_thresh_handler_th(struct iio_dev *dev_info,
				       int index,
				       s64 timestamp,
				       int no_test)
{
	struct lis3l02dq_state *st = dev_info->dev_data;

	/* Stash the timestamp somewhere convenient for the bh */
	st->last_timestamp = timestamp;
	schedule_work(&st->work_cont_thresh.ws);

	return 0;
}