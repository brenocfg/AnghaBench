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
typedef  int /*<<< orphan*/  u16_t ;
struct uip_tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  s8_t ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_ERR_OK ; 

__attribute__((used)) static s8_t tcpip_sent(void *arg,struct uip_tcp_pcb *pcb,u16_t space)
{
//	printf("tcpip_sent(%d)\n",space);
	return UIP_ERR_OK;
}