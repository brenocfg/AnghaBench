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

/* Variables and functions */
 int /*<<< orphan*/ * _pcb_main ; 
 int /*<<< orphan*/  udp_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _udp_pcb_main_deinit(void)
{
    if(_pcb_main){
        udp_recv(_pcb_main, NULL, NULL);
        udp_disconnect(_pcb_main);
        udp_remove(_pcb_main);
        _pcb_main = NULL;
    }
}