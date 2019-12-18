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
struct __vxge_hw_device {int link_state; } ;
typedef  enum vxge_hw_device_link_state { ____Placeholder_vxge_hw_device_link_state } vxge_hw_device_link_state ;

/* Variables and functions */

__attribute__((used)) static inline
enum vxge_hw_device_link_state vxge_hw_device_link_state_get(
	struct __vxge_hw_device *devh)
{
	return devh->link_state;
}