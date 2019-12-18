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
 int /*<<< orphan*/  ARP_TMR_INTERVAL ; 
 int /*<<< orphan*/  etharp_tmr () ; 
 int /*<<< orphan*/  sys_timeout (int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arp_timer(void *arg)
{
  etharp_tmr();
  sys_timeout(ARP_TMR_INTERVAL, arp_timer, NULL);
}