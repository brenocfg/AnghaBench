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
struct TYPE_2__ {size_t left; } ;

/* Variables and functions */
 TYPE_1__ parport_ip32_dma ; 

__attribute__((used)) static inline size_t parport_ip32_dma_get_residue(void)
{
	return parport_ip32_dma.left;
}