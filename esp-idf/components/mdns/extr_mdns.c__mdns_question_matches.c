#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {TYPE_5__* service; } ;
typedef  TYPE_1__ mdns_srv_item_t ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ domain; scalar_t__ proto; scalar_t__ service; scalar_t__ host; } ;
typedef  TYPE_2__ mdns_parsed_question_t ;
struct TYPE_8__ {char const* service; char const* proto; } ;

/* Variables and functions */
 char const* MDNS_DEFAULT_DOMAIN ; 
 scalar_t__ MDNS_TYPE_A ; 
 scalar_t__ MDNS_TYPE_AAAA ; 
 scalar_t__ MDNS_TYPE_PTR ; 
 scalar_t__ MDNS_TYPE_SDPTR ; 
 scalar_t__ MDNS_TYPE_SRV ; 
 scalar_t__ MDNS_TYPE_TXT ; 
 char* _mdns_get_service_instance_name (TYPE_5__*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,scalar_t__) ; 

__attribute__((used)) static bool _mdns_question_matches(mdns_parsed_question_t * question, uint16_t type, mdns_srv_item_t * service)
{
    if (question->type != type) {
        return false;
    }
    if (type == MDNS_TYPE_A || type == MDNS_TYPE_AAAA) {
        return true;
    } else if (type == MDNS_TYPE_PTR || type == MDNS_TYPE_SDPTR) {
        if (!strcasecmp(service->service->service, question->service)
            && !strcasecmp(service->service->proto, question->proto)
            && !strcasecmp(MDNS_DEFAULT_DOMAIN, question->domain)) {
            return true;
        }
    } else if (type == MDNS_TYPE_SRV || type == MDNS_TYPE_TXT) {
        const char * name = _mdns_get_service_instance_name(service->service);
        if (name && question->host && !strcasecmp(name, question->host)
            && !strcasecmp(service->service->service, question->service)
            && !strcasecmp(service->service->proto, question->proto)
            && !strcasecmp(MDNS_DEFAULT_DOMAIN, question->domain)) {
            return true;
        }
    }

    return false;
}