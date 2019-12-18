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
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  IP_ADDR_ANY ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UDP_DEBUG ; 
 int /*<<< orphan*/ * global_pcb ; 
 scalar_t__ udp_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * udp_new () ; 
 int /*<<< orphan*/  udp_process_recv_packet ; 
 int /*<<< orphan*/  udp_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void udp_recv_init(void)
{
    /* get new pcb */
    global_pcb = udp_new();
    if (global_pcb == NULL) {
        LWIP_DEBUGF(UDP_DEBUG, ("udp_new failed!\n"));
        return;
    }

    /* bind to any IP address on port 7 */
    if (udp_bind(global_pcb, IP_ADDR_ANY, 7) != ERR_OK) {
        LWIP_DEBUGF(UDP_DEBUG, ("udp_bind failed!\n"));
        return;
    }

    /* set udp_echo_recv() as callback function
       for received packets */
    udp_recv(global_pcb, udp_process_recv_packet, NULL);
}