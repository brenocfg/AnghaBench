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
struct uip_tcp_pcb {int dummy; } ;
struct uip_pbuf {int dummy; } ;
typedef  scalar_t__ s8_t ;

/* Variables and functions */
 scalar_t__ UIP_ERR_OK ; 
 int /*<<< orphan*/  uip_pbuf_free (struct uip_pbuf*) ; 
 scalar_t__ uip_tcp_close (struct uip_tcp_pcb*) ; 

__attribute__((used)) static s8_t uip_tcp_nullrecv(void *arg,struct uip_tcp_pcb *pcb,struct uip_pbuf *p,s8_t err)
{
	if(p!=NULL) uip_pbuf_free(p);
	else if(err==UIP_ERR_OK) return uip_tcp_close(pcb);

	return UIP_ERR_OK;
}