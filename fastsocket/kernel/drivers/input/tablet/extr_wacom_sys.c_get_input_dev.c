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
struct wacom_combo {TYPE_1__* wacom; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {struct input_dev* dev; } ;

/* Variables and functions */

__attribute__((used)) static struct input_dev * get_input_dev(struct wacom_combo *wcombo)
{
	return wcombo->wacom->dev;
}