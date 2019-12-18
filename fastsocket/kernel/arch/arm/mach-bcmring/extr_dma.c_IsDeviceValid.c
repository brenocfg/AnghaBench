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
typedef  scalar_t__ DMA_Device_t ;

/* Variables and functions */
 scalar_t__ DMA_NUM_DEVICE_ENTRIES ; 

__attribute__((used)) static inline int IsDeviceValid(DMA_Device_t device)
{
	return (device >= 0) && (device < DMA_NUM_DEVICE_ENTRIES);
}