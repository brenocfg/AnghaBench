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
struct TYPE_4__ {scalar_t__ name; scalar_t__ help; scalar_t__ help_free; struct TYPE_4__* text; scalar_t__ text_free; scalar_t__ name_free; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */
 scalar_t__ dlg_strempty () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
dlg_free_formitems(DIALOG_FORMITEM * items)
{
    int n;
    for (n = 0; items[n].name != 0; ++n) {
	if (items[n].name_free)
	    free(items[n].name);
	if (items[n].text_free)
	    free(items[n].text);
	if (items[n].help_free && items[n].help != dlg_strempty())
	    free(items[n].help);
    }
    free(items);
}