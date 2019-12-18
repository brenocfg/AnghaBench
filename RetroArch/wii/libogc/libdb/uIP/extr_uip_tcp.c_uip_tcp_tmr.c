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
 int /*<<< orphan*/  uip_tcp_fasttmr () ; 
 int /*<<< orphan*/  uip_tcp_slowtmr () ; 
 int uip_tcp_timer ; 

void uip_tcp_tmr()
{
	uip_tcp_fasttmr();

	if(++uip_tcp_timer&1) uip_tcp_slowtmr();
}