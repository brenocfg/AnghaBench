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
struct tcp_pcb {struct tcp_pcb* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_lwip_tcp_pcb_one_show (struct tcp_pcb*) ; 

__attribute__((used)) static void dbg_lwip_tcp_pcb_list_show(struct tcp_pcb* pcb)
{
    while(pcb){
        dbg_lwip_tcp_pcb_one_show(pcb);
        pcb = pcb->next;
    }
}