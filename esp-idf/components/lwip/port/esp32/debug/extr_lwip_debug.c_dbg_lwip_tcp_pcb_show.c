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
 int /*<<< orphan*/  ESP_LWIP_LOGI (char*) ; 
 int /*<<< orphan*/  dbg_lwip_tcp_pcb_list_show (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_active_pcbs ; 
 int /*<<< orphan*/  tcp_bound_pcbs ; 
 int /*<<< orphan*/  tcp_tw_pcbs ; 

void dbg_lwip_tcp_pcb_show(void)
{
    ESP_LWIP_LOGI("-------------active pcbs------------");
    dbg_lwip_tcp_pcb_list_show(tcp_active_pcbs);
    ESP_LWIP_LOGI("-------------bound pcbs-------------");
    dbg_lwip_tcp_pcb_list_show(tcp_bound_pcbs);
    ESP_LWIP_LOGI("-------------tw     pcbs------------");
    dbg_lwip_tcp_pcb_list_show(tcp_tw_pcbs);
}