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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Writer ;

/* Variables and functions */
 TYPE_1__ const** registered_writers ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const Writer *writer_get_by_name(const char *name)
{
    int i;

    for (i = 0; registered_writers[i]; i++)
        if (!strcmp(registered_writers[i]->name, name))
            return registered_writers[i];

    return NULL;
}