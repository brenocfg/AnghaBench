#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* interfaces; } ;
struct TYPE_5__ {TYPE_1__* pcbs; } ;
struct TYPE_4__ {scalar_t__ pcb; } ;

/* Variables and functions */
 int MDNS_IF_MAX ; 
 int MDNS_IP_PROTOCOL_MAX ; 
 TYPE_3__* _mdns_server ; 

__attribute__((used)) static bool _udp_pcb_is_in_use(void){
    int i, p;
    for (i=0; i<MDNS_IF_MAX; i++) {
        for (p=0; p<MDNS_IP_PROTOCOL_MAX; p++) {
            if(_mdns_server->interfaces[i].pcbs[p].pcb){
                return true;
            }
        }
    }
    return false;
}