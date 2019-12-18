#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int VAR_COUNT ; 
 scalar_t__ dlg_strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* vars ; 

__attribute__((used)) static int
find_vars(char *name)
{
    int result = -1;
    unsigned i;

    for (i = 0; i < VAR_COUNT; i++) {
	if (dlg_strcmp(vars[i].name, name) == 0) {
	    result = (int) i;
	    break;
	}
    }
    return result;
}