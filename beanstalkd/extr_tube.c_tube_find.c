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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Tube ;
struct TYPE_5__ {size_t len; TYPE_1__** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TUBE_NAME_LEN ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ tubes ; 

Tube *
tube_find(const char *name)
{
    size_t i;

    for (i = 0; i < tubes.len; i++) {
        Tube *t = tubes.items[i];
        if (strncmp(t->name, name, MAX_TUBE_NAME_LEN) == 0)
            return t;
    }
    return NULL;
}