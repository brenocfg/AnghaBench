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
struct wimax_dev {int /*<<< orphan*/  rfkill; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ ) ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 

void wimax_rfkill_rm(struct wimax_dev *wimax_dev)
{
	struct device *dev = wimax_dev_to_dev(wimax_dev);
	d_fnstart(3, dev, "(wimax_dev %p)\n", wimax_dev);
	rfkill_unregister(wimax_dev->rfkill);
	rfkill_destroy(wimax_dev->rfkill);
	d_fnend(3, dev, "(wimax_dev %p)\n", wimax_dev);
}