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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__* domain; scalar_t__* proto; scalar_t__* service; scalar_t__* host; } ;
typedef  TYPE_1__ mdns_name_t ;

/* Variables and functions */
 char* MDNS_DEFAULT_DOMAIN ; 
 scalar_t__ MDNS_TYPE_PTR ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__*,char*) ; 

__attribute__((used)) static bool _mdns_name_is_discovery(mdns_name_t * name, uint16_t type)
{
    return (
               (name->host && name->host[0] && !strcasecmp(name->host, "_services"))
               && (name->service && name->service[0] && !strcasecmp(name->service, "_dns-sd"))
               && (name->proto && name->proto[0] && !strcasecmp(name->proto, "_udp"))
               && (name->domain && name->domain[0] && !strcasecmp(name->domain, MDNS_DEFAULT_DOMAIN))
               && type == MDNS_TYPE_PTR
           );
}