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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ mdns_search_once_t ;
struct TYPE_5__ {TYPE_1__* search_once; } ;

/* Variables and functions */
 TYPE_2__* _mdns_server ; 

__attribute__((used)) static void _mdns_search_add(mdns_search_once_t * search)
{
    search->next = _mdns_server->search_once;
    _mdns_server->search_once = search;
}