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
struct TYPE_2__ {scalar_t__ tab_correct; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAB ; 
 TYPE_1__ dialog_vars ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 

void
dlg_tab_correct_str(char *prompt)
{
    char *ptr;

    if (dialog_vars.tab_correct) {
	while ((ptr = strchr(prompt, TAB)) != NULL) {
	    *ptr = ' ';
	    prompt = ptr;
	}
    }
}