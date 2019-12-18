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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u16_t ;
struct uip_tcp_pcb {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  s8_t ;

/* Variables and functions */
 scalar_t__ UIP_CLOSE_WAIT ; 
 int /*<<< orphan*/  UIP_ERR_CONN ; 
 int /*<<< orphan*/  UIP_ERR_OK ; 
 scalar_t__ UIP_ESTABLISHED ; 
 scalar_t__ UIP_SYN_RCVD ; 
 scalar_t__ UIP_SYN_SENT ; 
 int /*<<< orphan*/  uip_tcpenqueue (struct uip_tcp_pcb*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

s8_t uip_tcp_write(struct uip_tcp_pcb *pcb,const void *arg,u16_t len,u8_t copy)
{
	if(pcb->state==UIP_ESTABLISHED || pcb->state==UIP_CLOSE_WAIT ||
		pcb->state==UIP_SYN_SENT || pcb->state==UIP_SYN_RCVD) {
		if(len>0) {
			return uip_tcpenqueue(pcb,(void*)arg,len,0,copy,NULL,0);
		}
		return UIP_ERR_OK;
	}
	return UIP_ERR_CONN;
}