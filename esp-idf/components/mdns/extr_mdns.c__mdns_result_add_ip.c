#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_9__* addr; } ;
typedef  TYPE_8__ mdns_result_t ;
struct TYPE_18__ {int /*<<< orphan*/  addr; } ;
struct TYPE_16__ {scalar_t__ addr; } ;
struct TYPE_19__ {TYPE_3__ ip6; TYPE_1__ ip4; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_4__ u_addr; } ;
struct TYPE_24__ {struct TYPE_24__* next; TYPE_5__ addr; } ;
typedef  TYPE_9__ mdns_ip_addr_t ;
struct TYPE_21__ {int /*<<< orphan*/  addr; } ;
struct TYPE_17__ {scalar_t__ addr; } ;
struct TYPE_22__ {TYPE_6__ ip6; TYPE_2__ ip4; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_7__ u_addr; } ;
typedef  TYPE_10__ esp_ip_addr_t ;

/* Variables and functions */
 scalar_t__ IPADDR_TYPE_V4 ; 
 scalar_t__ IPADDR_TYPE_V6 ; 
 TYPE_9__* _mdns_result_addr_create_ip (TYPE_10__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _mdns_result_add_ip(mdns_result_t * r, esp_ip_addr_t * ip)
{
    mdns_ip_addr_t * a = r->addr;
    while (a) {
        if (a->addr.type == ip->type) {
            if (a->addr.type == IPADDR_TYPE_V4 && a->addr.u_addr.ip4.addr == ip->u_addr.ip4.addr) {
                return;
            }
            if (a->addr.type == IPADDR_TYPE_V6 && !memcmp(a->addr.u_addr.ip6.addr, ip->u_addr.ip6.addr, 16)) {
                return;
            }
        }
        a = a->next;
    }
    a = _mdns_result_addr_create_ip(ip);
    if (!a) {
        return;
    }
    a->next = r->addr;
    r->addr = a;
}