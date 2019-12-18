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
typedef  int /*<<< orphan*/  DIALOG_LISTITEM ;

/* Variables and functions */
 int DLG_EXIT_ERROR ; 

int
dlg_dummy_menutext(DIALOG_LISTITEM * items, int current, char *newtext)
{
    (void) items;
    (void) current;
    (void) newtext;
    return DLG_EXIT_ERROR;
}