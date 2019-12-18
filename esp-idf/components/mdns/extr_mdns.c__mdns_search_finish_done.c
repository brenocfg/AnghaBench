#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ max_results; scalar_t__ num_results; struct TYPE_4__* next; } ;
typedef  TYPE_1__ mdns_search_once_t ;
struct TYPE_5__ {TYPE_1__* search_once; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mdns_search_finish (TYPE_1__*) ; 
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static void _mdns_search_finish_done(void)
{
    mdns_search_once_t * search = _mdns_server->search_once;
    mdns_search_once_t * s = NULL;
    while (search) {
        s = search;
        search = search->next;
        if (s->max_results && s->num_results >= s->max_results) {
            _mdns_search_finish(s);
        }
    }
}