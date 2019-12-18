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
struct wahc {int /*<<< orphan*/  rpipe_bm; int /*<<< orphan*/  rpipes; TYPE_1__* usb_iface; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_scnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void wa_rpipes_destroy(struct wahc *wa)
{
	struct device *dev = &wa->usb_iface->dev;

	if (!bitmap_empty(wa->rpipe_bm, wa->rpipes)) {
		char buf[256];
		WARN_ON(1);
		bitmap_scnprintf(buf, sizeof(buf), wa->rpipe_bm, wa->rpipes);
		dev_err(dev, "BUG: pipes not released on exit: %s\n", buf);
	}
	kfree(wa->rpipe_bm);
}