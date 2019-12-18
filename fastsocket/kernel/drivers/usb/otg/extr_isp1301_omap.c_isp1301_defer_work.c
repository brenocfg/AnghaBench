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
struct isp1301 {TYPE_1__* client; int /*<<< orphan*/  working; int /*<<< orphan*/  work; int /*<<< orphan*/  todo; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isp1301_defer_work(struct isp1301 *isp, int work)
{
	int status;

	if (isp && !test_and_set_bit(work, &isp->todo)) {
		(void) get_device(&isp->client->dev);
		status = schedule_work(&isp->work);
		if (!status && !isp->working)
			dev_vdbg(&isp->client->dev,
				"work item %d may be lost\n", work);
	}
}