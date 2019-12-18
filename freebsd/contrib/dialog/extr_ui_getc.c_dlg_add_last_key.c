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
struct TYPE_2__ {scalar_t__ last_key; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_add_separator () ; 
 int /*<<< orphan*/  dlg_add_string (char*) ; 
 scalar_t__ dlg_need_separator () ; 
 int last_getc ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
dlg_add_last_key(int mode)
{
    if (dialog_vars.last_key) {
	if (mode >= 0) {
	    if (mode > 0) {
		dlg_add_last_key(-1);
	    } else {
		if (dlg_need_separator())
		    dlg_add_separator();
		dlg_add_last_key(-2);
	    }
	} else {
	    char temp[80];
	    sprintf(temp, "%d", last_getc);
	    dlg_add_string(temp);
	    if (mode == -1)
		dlg_add_separator();
	}
    }
}