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
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ Shell ;

/* Variables and functions */
 TYPE_1__* shells ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Shell *
JobMatchShell(const char *name)
{
    Shell	*sh;

    for (sh = shells; sh->name != NULL; sh++) {
	if (strcmp(name, sh->name) == 0)
		return (sh);
    }
    return NULL;
}