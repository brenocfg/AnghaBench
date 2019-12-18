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
struct TYPE_4__ {int /*<<< orphan*/  done_semaphore; struct TYPE_4__* proto; struct TYPE_4__* service; struct TYPE_4__* instance; } ;
typedef  TYPE_1__ mdns_search_once_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _mdns_search_free(mdns_search_once_t * search)
{
    free(search->instance);
    free(search->service);
    free(search->proto);
    vSemaphoreDelete(search->done_semaphore);
    free(search);
}