#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ default_item; } ;
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */
 TYPE_3__ dialog_vars ; 
 int /*<<< orphan*/  strcmp (scalar_t__,scalar_t__) ; 

int
dlg_default_formitem(DIALOG_FORMITEM * items)
{
    int result = 0;

    if (dialog_vars.default_item != 0) {
	int count = 0;
	while (items->name != 0) {
	    if (!strcmp(dialog_vars.default_item, items->name)) {
		result = count;
		break;
	    }
	    ++items;
	    count++;
	}
    }
    return result;
}