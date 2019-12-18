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
struct ibmvscsi_host_data {scalar_t__ reenable_crq; scalar_t__ reset_crq; } ;

/* Variables and functions */
 scalar_t__ kthread_should_stop () ; 

__attribute__((used)) static int ibmvscsi_work_to_do(struct ibmvscsi_host_data *hostdata)
{
	if (kthread_should_stop())
		return 1;
	else if (hostdata->reset_crq) {
		return 1;
	} else if (hostdata->reenable_crq) {
		return 1;
	}

	return 0;
}