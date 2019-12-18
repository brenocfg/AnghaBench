#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  target ;
struct uwb_dev_addr {int dummy; } ;
struct TYPE_8__ {scalar_t__ type; struct uwb_dev_addr devaddr; TYPE_2__* dev; } ;
struct uwb_rsv {int /*<<< orphan*/  state; TYPE_3__ target; TYPE_1__* owner; TYPE_5__* rc; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  owner ;
struct TYPE_9__ {struct device dev; } ;
struct TYPE_10__ {TYPE_4__ uwb_dev; } ;
struct TYPE_7__ {struct uwb_dev_addr dev_addr; } ;
struct TYPE_6__ {struct uwb_dev_addr dev_addr; } ;

/* Variables and functions */
 int UWB_ADDR_STRSIZE ; 
 scalar_t__ UWB_RSV_TARGET_DEV ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_dev_addr_print (char*,int,struct uwb_dev_addr*) ; 
 int /*<<< orphan*/  uwb_rsv_state_str (int /*<<< orphan*/ ) ; 

void uwb_rsv_dump(char *text, struct uwb_rsv *rsv)
{
	struct device *dev = &rsv->rc->uwb_dev.dev;
	struct uwb_dev_addr devaddr;
	char owner[UWB_ADDR_STRSIZE], target[UWB_ADDR_STRSIZE];

	uwb_dev_addr_print(owner, sizeof(owner), &rsv->owner->dev_addr);
	if (rsv->target.type == UWB_RSV_TARGET_DEV)
		devaddr = rsv->target.dev->dev_addr;
	else
		devaddr = rsv->target.devaddr;
	uwb_dev_addr_print(target, sizeof(target), &devaddr);

	dev_dbg(dev, "rsv %s %s -> %s: %s\n",
		text, owner, target, uwb_rsv_state_str(rsv->state));
}