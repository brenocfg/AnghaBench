#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {scalar_t__ max_results; scalar_t__ num_results; TYPE_2__* result; } ;
typedef  TYPE_1__ mdns_search_once_t ;
struct TYPE_7__ {scalar_t__ tcpip_if; scalar_t__ ip_protocol; struct TYPE_7__* next; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_2__ mdns_result_t ;
typedef  scalar_t__ mdns_ip_protocol_t ;
typedef  scalar_t__ mdns_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 int /*<<< orphan*/  _str_null_or_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void _mdns_search_result_add_srv(mdns_search_once_t * search, const char * hostname, uint16_t port, mdns_if_t tcpip_if, mdns_ip_protocol_t ip_protocol)
{
    mdns_result_t * r = search->result;
    while (r) {
        if (r->tcpip_if == tcpip_if && r->ip_protocol == ip_protocol && !_str_null_or_empty(r->hostname) && !strcasecmp(hostname, r->hostname)) {
            return;
        }
        r = r->next;
    }
    if (!search->max_results || search->num_results < search->max_results) {
        r = (mdns_result_t *)malloc(sizeof(mdns_result_t));
        if (!r) {
            HOOK_MALLOC_FAILED;
            return;
        }

        memset(r, 0 , sizeof(mdns_result_t));
        r->hostname = strdup(hostname);
        if (!r->hostname) {
            free(r);
            return;
        }
        r->port = port;
        r->tcpip_if = tcpip_if;
        r->ip_protocol = ip_protocol;
        r->next = search->result;
        search->result = r;
        search->num_results++;
    }
}