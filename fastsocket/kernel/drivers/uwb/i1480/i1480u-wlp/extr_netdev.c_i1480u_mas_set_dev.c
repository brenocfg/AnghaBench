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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct uwb_dev {int /*<<< orphan*/  dev_addr; } ;
typedef  int /*<<< orphan*/  rcaddrbuf ;
typedef  int /*<<< orphan*/  devaddrbuf ;

/* Variables and functions */
 int UWB_ADDR_STRSIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,char*,int) ; 
 int i1480u_set_ip_mas (struct uwb_rc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  uwb_dev_addr_print (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i1480u_mas_set_dev(struct uwb_dev *uwb_dev, struct uwb_rc *rc,
			      u8 stream, u8 owner, u8 type, unsigned long *mas)
{
	int result = 0;
	struct device *dev = &rc->uwb_dev.dev;

	result = i1480u_set_ip_mas(rc, &uwb_dev->dev_addr, stream, owner,
				   type, mas);
	if (result < 0) {
		char rcaddrbuf[UWB_ADDR_STRSIZE], devaddrbuf[UWB_ADDR_STRSIZE];
		uwb_dev_addr_print(rcaddrbuf, sizeof(rcaddrbuf),
				   &rc->uwb_dev.dev_addr);
		uwb_dev_addr_print(devaddrbuf, sizeof(devaddrbuf),
				   &uwb_dev->dev_addr);
		dev_err(dev, "Set IP MAS (%s to %s) failed: %d\n",
			rcaddrbuf, devaddrbuf, result);
	}
	return result;
}