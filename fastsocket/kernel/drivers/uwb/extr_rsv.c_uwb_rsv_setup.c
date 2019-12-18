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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {int /*<<< orphan*/ * rsv_workq; TYPE_1__ uwb_dev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * create_singlethread_workqueue (char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int uwb_rsv_setup(struct uwb_rc *rc)
{
	char name[16];

	snprintf(name, sizeof(name), "%s_rsvd", dev_name(&rc->uwb_dev.dev));
	rc->rsv_workq = create_singlethread_workqueue(name);
	if (rc->rsv_workq == NULL)
		return -ENOMEM;

	return 0;
}