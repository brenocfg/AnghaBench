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
struct uwb_dev {int /*<<< orphan*/  rc; } ;
struct uwb_beca_e {struct uwb_dev* uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NOTIF_OFFAIR ; 
 int /*<<< orphan*/  __uwb_dev_offair (struct uwb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_notify (int /*<<< orphan*/ ,struct uwb_dev*,int /*<<< orphan*/ ) ; 

void uwbd_dev_offair(struct uwb_beca_e *bce)
{
	struct uwb_dev *uwb_dev;

	uwb_dev = bce->uwb_dev;
	if (uwb_dev) {
		uwb_notify(uwb_dev->rc, uwb_dev, UWB_NOTIF_OFFAIR);
		__uwb_dev_offair(uwb_dev, uwb_dev->rc);
	}
}