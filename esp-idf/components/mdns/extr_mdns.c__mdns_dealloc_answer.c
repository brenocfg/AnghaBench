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
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ service; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ mdns_srv_item_t ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ service; struct TYPE_7__* next; } ;
typedef  TYPE_2__ mdns_out_answer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void _mdns_dealloc_answer(mdns_out_answer_t ** destnation, uint16_t type, mdns_srv_item_t * service)
{
    mdns_out_answer_t * d = *destnation;
    if (!d) {
        return;
    }
    mdns_srv_item_t s = {NULL, NULL};
    if (!service) {
        service = &s;
    }
    if (d->type == type && d->service == service->service) {
        *destnation = d->next;
        free(d);
        return;
    }
    while (d->next) {
        mdns_out_answer_t * a = d->next;
        if (a->type == type && a->service == service->service) {
            d->next = a->next;
            free(a);
            return;
        }
        d = d->next;
    }
}