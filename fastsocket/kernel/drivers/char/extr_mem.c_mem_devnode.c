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
struct device {int /*<<< orphan*/  devt; } ;
typedef  scalar_t__ mode_t ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 size_t MINOR (int /*<<< orphan*/ ) ; 
 TYPE_1__* devlist ; 

__attribute__((used)) static char *mem_devnode(struct device *dev, mode_t *mode)
{
	if (mode && devlist[MINOR(dev->devt)].mode)
		*mode = devlist[MINOR(dev->devt)].mode;
	return NULL;
}