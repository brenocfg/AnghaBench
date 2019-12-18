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
struct TYPE_4__ {TYPE_1__* hcam; int /*<<< orphan*/  msg; } ;
struct pmcraid_instance {TYPE_2__ ccn; } ;
struct pmcraid_hcam_hdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ data_len; } ;

/* Variables and functions */
 int pmcraid_notify_aen (struct pmcraid_instance*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pmcraid_notify_ccn(struct pmcraid_instance *pinstance)
{
	return pmcraid_notify_aen(pinstance,
				pinstance->ccn.msg,
				pinstance->ccn.hcam->data_len +
				sizeof(struct pmcraid_hcam_hdr));
}