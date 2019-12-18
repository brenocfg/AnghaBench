#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_3__ {scalar_t__ addr; } ;
typedef  TYPE_1__ esp_ip6_addr_t ;

/* Variables and functions */
 size_t _MDNS_SIZEOF_IP6_ADDR ; 

__attribute__((used)) static bool _ipv6_address_is_zero(esp_ip6_addr_t ip6)
{
    uint8_t i;
    uint8_t * data = (uint8_t *)ip6.addr;
    for (i=0; i<_MDNS_SIZEOF_IP6_ADDR; i++) {
        if (data[i]) {
            return false;
        }
    }
    return true;
}