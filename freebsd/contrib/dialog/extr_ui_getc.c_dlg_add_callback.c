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
struct TYPE_5__ {TYPE_1__* getc_callbacks; } ;
struct TYPE_4__ {int /*<<< orphan*/  win; struct TYPE_4__* next; } ;
typedef  TYPE_1__ DIALOG_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  WTIMEOUT_VAL ; 
 TYPE_3__ dialog_state ; 
 int /*<<< orphan*/  wtimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dlg_add_callback(DIALOG_CALLBACK * p)
{
    p->next = dialog_state.getc_callbacks;
    dialog_state.getc_callbacks = p;
    wtimeout(p->win, WTIMEOUT_VAL);
}