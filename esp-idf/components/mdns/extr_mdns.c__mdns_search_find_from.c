#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ type; struct TYPE_7__* next; int /*<<< orphan*/ * proto; int /*<<< orphan*/ * service; int /*<<< orphan*/ * instance; TYPE_2__* result; } ;
typedef  TYPE_1__ mdns_search_once_t ;
struct TYPE_8__ {scalar_t__ tcpip_if; scalar_t__ ip_protocol; struct TYPE_8__* next; int /*<<< orphan*/ * hostname; } ;
typedef  TYPE_2__ mdns_result_t ;
struct TYPE_9__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  service; int /*<<< orphan*/  host; } ;
typedef  TYPE_3__ mdns_name_t ;
typedef  scalar_t__ mdns_ip_protocol_t ;
typedef  scalar_t__ mdns_if_t ;

/* Variables and functions */
 scalar_t__ MDNS_TYPE_A ; 
 scalar_t__ MDNS_TYPE_AAAA ; 
 scalar_t__ MDNS_TYPE_ANY ; 
 scalar_t__ MDNS_TYPE_PTR ; 
 scalar_t__ MDNS_TYPE_SRV ; 
 scalar_t__ MDNS_TYPE_TXT ; 
 scalar_t__ SEARCH_OFF ; 
 int /*<<< orphan*/  _str_null_or_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mdns_search_once_t * _mdns_search_find_from(mdns_search_once_t * s, mdns_name_t * name, uint16_t type, mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    mdns_result_t * r = NULL;
    while (s) {
        if (s->state == SEARCH_OFF) {
            s = s->next;
            continue;
        }

        if (type == MDNS_TYPE_A || type == MDNS_TYPE_AAAA) {
            if ((s->type == MDNS_TYPE_ANY && s->service != NULL)
                || (s->type != MDNS_TYPE_ANY && s->type != type && s->type != MDNS_TYPE_PTR))
            {
                s = s->next;
                continue;
            }
            if (s->type != MDNS_TYPE_PTR) {
                if (!strcasecmp(name->host, s->instance)) {
                    return s;
                }
                s = s->next;
                continue;
            }
            r = s->result;
            while (r) {
                if (r->tcpip_if == tcpip_if && r->ip_protocol == ip_protocol && !_str_null_or_empty(r->hostname) && !strcasecmp(name->host, r->hostname)) {
                    return s;
                }
                r = r->next;
            }
            s = s->next;
            continue;
        }

        if (type == MDNS_TYPE_SRV || type == MDNS_TYPE_TXT) {
            if ((s->type == MDNS_TYPE_ANY && s->service == NULL)
                || (s->type != MDNS_TYPE_ANY && s->type != type && s->type != MDNS_TYPE_PTR))
            {
                s = s->next;
                continue;
            }
            if (strcasecmp(name->service, s->service)
                || strcasecmp(name->proto, s->proto))
            {
                s = s->next;
                continue;
            }
            if (s->type != MDNS_TYPE_PTR) {
                if (!strcasecmp(name->host, s->instance)) {
                    return s;
                }
                s = s->next;
                continue;
            }
            return s;
        }

        if (type == MDNS_TYPE_PTR && type == s->type && !strcasecmp(name->service, s->service) && !strcasecmp(name->proto, s->proto)) {
            return s;
        }

        s = s->next;
    }

    return NULL;
}