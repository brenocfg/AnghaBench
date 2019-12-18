#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; int /*<<< orphan*/  area; } ;
typedef  TYPE_1__ YuiWindow ;

/* Variables and functions */
 int /*<<< orphan*/  YUI_GL (int /*<<< orphan*/ ) ; 
 int YUI_IS_RUNNING ; 
 int /*<<< orphan*/  yui_gl_draw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_gl_draw_pause (int /*<<< orphan*/ ) ; 

void yui_window_update(YuiWindow * yui) {

  if (!(yui->state & YUI_IS_RUNNING)) yui_gl_draw_pause(YUI_GL(yui->area));
  else yui_gl_draw(YUI_GL(yui->area));
}