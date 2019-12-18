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
struct sys_device {int dummy; } ;
struct etr_aib {int dummy; } ;

/* Variables and functions */
 struct etr_aib etr_port0 ; 
 struct sys_device etr_port0_dev ; 
 scalar_t__ etr_port0_online ; 
 struct etr_aib etr_port1 ; 
 scalar_t__ etr_port1_online ; 

__attribute__((used)) static inline struct etr_aib *etr_aib_from_dev(struct sys_device *dev)
{
	if (dev == &etr_port0_dev)
		return etr_port0_online ? &etr_port0 : NULL;
	else
		return etr_port1_online ? &etr_port1 : NULL;
}