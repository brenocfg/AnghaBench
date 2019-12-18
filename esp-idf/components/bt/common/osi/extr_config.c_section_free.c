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
struct TYPE_3__ {int /*<<< orphan*/  entries; struct TYPE_3__* name; } ;
typedef  TYPE_1__ section_t ;

/* Variables and functions */
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 

__attribute__((used)) static void section_free(void *ptr)
{
    if (!ptr) {
        return;
    }

    section_t *section = ptr;
    osi_free(section->name);
    list_free(section->entries);
    osi_free(section);
}