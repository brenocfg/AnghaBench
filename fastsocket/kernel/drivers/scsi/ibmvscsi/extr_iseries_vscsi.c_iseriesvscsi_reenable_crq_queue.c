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
struct ibmvscsi_host_data {int dummy; } ;
struct crq_queue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int iseriesvscsi_reenable_crq_queue(struct crq_queue *queue,
					   struct ibmvscsi_host_data *hostdata)
{
	return 0;
}