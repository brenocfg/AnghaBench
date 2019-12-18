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
typedef  scalar_t__ mdns_if_t ;

/* Variables and functions */
 scalar_t__ MDNS_IF_ETH ; 
 scalar_t__ MDNS_IF_MAX ; 
 scalar_t__ MDNS_IF_STA ; 

__attribute__((used)) static mdns_if_t _mdns_get_other_if (mdns_if_t tcpip_if)
{
    if (tcpip_if == MDNS_IF_STA) {
        return MDNS_IF_ETH;
    } else if (tcpip_if == MDNS_IF_ETH) {
        return MDNS_IF_STA;
    }
    return MDNS_IF_MAX;
}