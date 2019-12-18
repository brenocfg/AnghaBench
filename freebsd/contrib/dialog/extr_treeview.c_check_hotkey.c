#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ no_tags; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ DIALOG_LISTITEM ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_2__ dialog_vars ; 
 int /*<<< orphan*/  dlg_last_getc () ; 
 scalar_t__ dlg_match_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_hotkey(DIALOG_LISTITEM * items, int choice)
{
    bool result = FALSE;

    if (dlg_match_char(dlg_last_getc(),
		       (dialog_vars.no_tags
			? items[choice].text
			: items[choice].name))) {
	result = TRUE;
    }
    return result;
}