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
struct TYPE_2__ {scalar_t__ quoted; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_add_quoted (char*) ; 
 int /*<<< orphan*/  dlg_add_result (char*) ; 

void
dlg_add_string(char *string)
{
    if (dialog_vars.quoted) {
	dlg_add_quoted(string);
    } else {
	dlg_add_result(string);
    }
}