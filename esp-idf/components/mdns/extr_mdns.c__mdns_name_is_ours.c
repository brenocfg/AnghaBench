#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  service; } ;
typedef  TYPE_1__ mdns_srv_item_t ;
struct TYPE_7__ {char const* domain; char const* service; char const* proto; char const* host; } ;
typedef  TYPE_2__ mdns_name_t ;
struct TYPE_8__ {char const* hostname; } ;

/* Variables and functions */
 char const* MDNS_DEFAULT_DOMAIN ; 
 char* _mdns_get_service_instance_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* _mdns_get_service_item (char const*,char const*) ; 
 TYPE_3__* _mdns_server ; 
 scalar_t__ _str_null_or_empty (char const*) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 

__attribute__((used)) static bool _mdns_name_is_ours(mdns_name_t * name)
{
    //domain have to be "local"
    if (_str_null_or_empty(name->domain) || strcasecmp(name->domain, MDNS_DEFAULT_DOMAIN)) {
        return false;
    }

    //if service and proto are empty, host must match out hostname
    if (_str_null_or_empty(name->service) && _str_null_or_empty(name->proto)) {
        if (!_str_null_or_empty(name->host)
          && !_str_null_or_empty(_mdns_server->hostname)
          && strcasecmp(name->host, _mdns_server->hostname) == 0)
        {
            return true;
        }
        return false;
    }

    //if service or proto is empty, name is invalid
    if (_str_null_or_empty(name->service) || _str_null_or_empty(name->proto)) {
        return false;
    }

    //find the service
    mdns_srv_item_t * service = _mdns_get_service_item(name->service, name->proto);
    if (!service) {
        return false;
    }

    //if host is empty and we have service, we have success
    if (_str_null_or_empty(name->host)) {
        return true;
    }

    //OK we have host in the name. find what is the instance of the service
    const char * instance = _mdns_get_service_instance_name(service->service);
    if (instance == NULL) {
        return false;
    }

    //compare the instance against the name
    if (strcasecmp(name->host, instance) == 0) {
        return true;
    }

    return false;
}