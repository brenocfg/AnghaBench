#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mdns_service_t ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * service; } ;
typedef  TYPE_1__ mdns_out_answer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void _mdns_dealloc_scheduled_service_answers(mdns_out_answer_t ** destination, mdns_service_t * service)
{
    mdns_out_answer_t * d = *destination;
    if (!d) {
        return;
    }
    while (d && d->service == service) {
        *destination = d->next;
        free(d);
        d = *destination;
    }
    while (d && d->next) {
        mdns_out_answer_t * a = d->next;
        if (a->service == service) {
            d->next = a->next;
            free(a);
        } else {
            d = d->next;
        }
    }
}