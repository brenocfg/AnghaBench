#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int start; scalar_t__ addr; } ;
struct TYPE_4__ {int slc0_rx_rst; } ;
struct TYPE_6__ {TYPE_2__ slc0_rx_link; TYPE_1__ conf0; } ;

/* Variables and functions */
 TYPE_3__ SLC ; 

__attribute__((used)) static inline void send_start_transmission(const void* desc)
{
    //reset to flush previous packets
    SLC.conf0.slc0_rx_rst = 1;
    SLC.conf0.slc0_rx_rst = 0;
    SLC.slc0_rx_link.addr = (uint32_t)desc;
    SLC.slc0_rx_link.start = 1;
}