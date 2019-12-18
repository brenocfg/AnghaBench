#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int DLG_EXIT_UNKNOWN ; 
 int /*<<< orphan*/  dlg_flush_getc () ; 
 int /*<<< orphan*/  dlg_last_getc () ; 
 scalar_t__ dlg_toupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* get_hotkeys (char const**) ; 

int
dlg_char_to_button(int ch, const char **labels)
{
    int result = DLG_EXIT_UNKNOWN;

    if (labels != 0) {
	int *hotkeys = get_hotkeys(labels);
	int j;

	ch = (int) dlg_toupper(dlg_last_getc());

	if (hotkeys != 0) {
	    for (j = 0; labels[j] != 0; ++j) {
		if (ch == hotkeys[j]) {
		    dlg_flush_getc();
		    result = j;
		    break;
		}
	    }
	    free(hotkeys);
	}
    }

    return result;
}