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
struct udp_pcb {void* remote_port; void* recv_arg; struct udp_pcb* recv; struct udp_pcb* local_port; int /*<<< orphan*/  flags; scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_LWIP_IP_PCB_SHOW (struct udp_pcb*) ; 
 int /*<<< orphan*/  ESP_LWIP_LOGI (char*,struct udp_pcb*,...) ; 

void dbg_lwip_udp_pcb_one_show(struct udp_pcb *pcb)
{
    ESP_LWIP_LOGI("pcb=%p next=%p", pcb, (void*)pcb->next);
    DBG_LWIP_IP_PCB_SHOW(pcb);
    ESP_LWIP_LOGI("flags=%x", pcb->flags);
    ESP_LWIP_LOGI("local_port=%d remote_port=%d", pcb->local_port, pcb->remote_port);
    ESP_LWIP_LOGI("recv cb=%p recv_arg=%p", pcb->recv, pcb->recv_arg);
}