#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ use_shadow; } ;
struct TYPE_3__ {scalar_t__ size_err; } ;

/* Variables and functions */
 int COLS ; 
 int LINES ; 
 int SCOLS ; 
 int SLINES ; 
 TYPE_2__ dialog_state ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_exiterr (char*,int,int,int,int) ; 

void
dlg_ctl_size(int height, int width)
{
    if (dialog_vars.size_err) {
	if ((width > COLS) || (height > LINES)) {
	    dlg_exiterr("Window too big. (height, width) = (%d, %d). Max allowed (%d, %d).",
			height, width, LINES, COLS);
	}
#ifdef HAVE_COLOR
	else if ((dialog_state.use_shadow)
		 && ((width > SCOLS || height > SLINES))) {
	    if ((width <= COLS) && (height <= LINES)) {
		/* try again, without shadows */
		dialog_state.use_shadow = 0;
	    } else {
		dlg_exiterr("Window+Shadow too big. (height, width) = (%d, %d). Max allowed (%d, %d).",
			    height, width, SLINES, SCOLS);
	    }
	}
#endif
    }
}