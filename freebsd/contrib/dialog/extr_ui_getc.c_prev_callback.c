#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* getc_callbacks; TYPE_1__* getc_redirect; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ DIALOG_CALLBACK ;

/* Variables and functions */
 TYPE_4__ dialog_state ; 

__attribute__((used)) static DIALOG_CALLBACK *
prev_callback(DIALOG_CALLBACK * p)
{
    DIALOG_CALLBACK *q;

    if ((p = dialog_state.getc_redirect) != 0) {
	if (p == dialog_state.getc_callbacks) {
	    for (p = dialog_state.getc_callbacks; p->next != 0; p = p->next) ;
	} else {
	    for (q = dialog_state.getc_callbacks; q->next != p; q = q->next) ;
	    p = q;
	}
    } else {
	p = dialog_state.getc_callbacks;
    }
    return p;
}