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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int sun4v_build_irq (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int sun4v_vdev_irq_build(struct device_node *dp,
					 unsigned int devino,
					 void *_data)
{
	u32 devhandle = (u32) (unsigned long) _data;

	return sun4v_build_irq(devhandle, devino);
}