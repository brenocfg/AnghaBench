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
struct TYPE_3__ {int stop; } ;
struct TYPE_4__ {TYPE_1__ slc0_rx_link; } ;

/* Variables and functions */
 TYPE_2__ SLC ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  send_intr_disable () ; 
 int /*<<< orphan*/  send_set_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_stop(void)
{
    SLC.slc0_rx_link.stop = 1;
    send_intr_disable();

    send_set_state(STATE_IDLE);
}