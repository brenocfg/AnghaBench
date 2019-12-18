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
struct TYPE_2__ {void* eba1; void* eba0; } ;
union chan_param_mem {TYPE_1__ pp; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static void ipu_ch_param_set_buffer(union chan_param_mem *params,
				    dma_addr_t buf0, dma_addr_t buf1)
{
	params->pp.eba0 = buf0;
	params->pp.eba1 = buf1;
}