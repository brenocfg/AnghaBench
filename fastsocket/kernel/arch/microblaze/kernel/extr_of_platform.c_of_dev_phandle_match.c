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
struct device {int dummy; } ;
typedef  scalar_t__ phandle ;
struct TYPE_4__ {TYPE_1__* node; } ;
struct TYPE_3__ {scalar_t__ linux_phandle; } ;

/* Variables and functions */
 TYPE_2__* to_of_device (struct device*) ; 

__attribute__((used)) static int of_dev_phandle_match(struct device *dev, void *data)
{
	phandle *ph = data;
	return to_of_device(dev)->node->linux_phandle == *ph;
}