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
struct TYPE_4__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ section_t ;

/* Variables and functions */
 int /*<<< orphan*/  entry_free ; 
 int /*<<< orphan*/  list_new (int /*<<< orphan*/ ) ; 
 TYPE_1__* osi_calloc (int) ; 
 int /*<<< orphan*/  osi_strdup (char const*) ; 

__attribute__((used)) static section_t *section_new(const char *name)
{
    section_t *section = osi_calloc(sizeof(section_t));
    if (!section) {
        return NULL;
    }

    section->name = osi_strdup(name);
    section->entries = list_new(entry_free);
    return section;
}