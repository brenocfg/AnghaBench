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
struct TYPE_2__ {scalar_t__ pipe_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ dialog_state ; 
 int dlg_progressbox (char const*,char const*,int,int,int /*<<< orphan*/ ,scalar_t__) ; 

int
dialog_progressbox(const char *title, const char *cprompt, int height, int width)
{
    int result;
    result = dlg_progressbox(title,
			     cprompt,
			     height,
			     width,
			     FALSE,
			     dialog_state.pipe_input);
    dialog_state.pipe_input = 0;
    return result;
}