#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rx_new_packet; } ;
struct TYPE_8__ {TYPE_2__ slc0_int_clr; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_done; } ;
struct TYPE_7__ {TYPE_1__ slc0_int_raw; } ;

/* Variables and functions */
 TYPE_4__ HOST ; 
 TYPE_3__ SLC ; 
 int /*<<< orphan*/  send_start_transmission (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_stop_ll_operation () ; 
 int /*<<< orphan*/  start_desc ; 

__attribute__((used)) static inline void send_isr_invoker_enable(void)
{
    //force trigger rx_done interrupt. the interrupt is abused to invoke ISR from the app by the enable bit and never cleared.
    send_start_transmission(&start_desc);
    //wait for rx_done
    while(!SLC.slc0_int_raw.rx_done);
    HOST.slc0_int_clr.rx_new_packet = 1;
    send_stop_ll_operation();
}