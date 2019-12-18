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
struct TYPE_2__ {scalar_t__ default_item; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

int
dlg_default_item(char **items, int llen)
{
    int result = 0;

    if (dialog_vars.default_item != 0) {
	int count = 0;
	while (*items != 0) {
	    if (!strcmp(dialog_vars.default_item, *items)) {
		result = count;
		break;
	    }
	    items += llen;
	    count++;
	}
    }
    return result;
}