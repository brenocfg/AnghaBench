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
 int /*<<< orphan*/  ETHARP_STATS_DISPLAY () ; 
 int /*<<< orphan*/  ICMP6_STATS_DISPLAY () ; 
 int /*<<< orphan*/  ICMP_STATS_DISPLAY () ; 
 int /*<<< orphan*/  IGMP_STATS_DISPLAY () ; 
 int /*<<< orphan*/  IP6_FRAG_STATS_DISPLAY () ; 
 int /*<<< orphan*/  IP6_STATS_DISPLAY () ; 
 int /*<<< orphan*/  IPFRAG_STATS_DISPLAY () ; 
 int /*<<< orphan*/  IP_STATS_DISPLAY () ; 
 int /*<<< orphan*/  LINK_STATS_DISPLAY () ; 
 int /*<<< orphan*/  MEM_STATS_DISPLAY () ; 
 int /*<<< orphan*/  MLD6_STATS_DISPLAY () ; 
 int /*<<< orphan*/  ND6_STATS_DISPLAY () ; 
 int /*<<< orphan*/  SYS_STATS_DISPLAY () ; 
 int /*<<< orphan*/  TCP_STATS_DISPLAY () ; 
 int /*<<< orphan*/  UDP_STATS_DISPLAY () ; 

void dbg_lwip_stats_show(void)
{
    TCP_STATS_DISPLAY();
    UDP_STATS_DISPLAY();
    ICMP_STATS_DISPLAY();
    IGMP_STATS_DISPLAY();
    IP_STATS_DISPLAY();
    IPFRAG_STATS_DISPLAY();
    ETHARP_STATS_DISPLAY();
    LINK_STATS_DISPLAY();
    MEM_STATS_DISPLAY();
    SYS_STATS_DISPLAY();
    IP6_STATS_DISPLAY();
    ICMP6_STATS_DISPLAY();
    IP6_FRAG_STATS_DISPLAY();
    MLD6_STATS_DISPLAY();
    ND6_STATS_DISPLAY();
}