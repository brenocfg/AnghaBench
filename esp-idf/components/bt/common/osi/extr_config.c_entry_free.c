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
struct TYPE_3__ {struct TYPE_3__* value; struct TYPE_3__* key; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 

__attribute__((used)) static void entry_free(void *ptr)
{
    if (!ptr) {
        return;
    }

    entry_t *entry = ptr;
    osi_free(entry->key);
    osi_free(entry->value);
    osi_free(entry);
}