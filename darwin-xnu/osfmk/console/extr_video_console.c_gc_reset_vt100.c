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
struct TYPE_2__ {int /*<<< orphan*/  v_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_NONE ; 
 int /*<<< orphan*/  COLOR_BACKGROUND ; 
 int /*<<< orphan*/  COLOR_FOREGROUND ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gc_attr ; 
 scalar_t__* gc_charset ; 
 scalar_t__ gc_charset_select ; 
 scalar_t__ gc_relative_origin ; 
 int /*<<< orphan*/  gc_reset_tabs () ; 
 int /*<<< orphan*/  gc_scrreg_bottom ; 
 scalar_t__ gc_scrreg_top ; 
 int /*<<< orphan*/  gc_update_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gc_wrap_mode ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void
gc_reset_vt100(void)
{
	gc_reset_tabs();
	gc_scrreg_top    = 0;
	gc_scrreg_bottom = vinfo.v_rows;
	gc_attr = ATTR_NONE;
	gc_charset[0] = gc_charset[1] = 0;
	gc_charset_select = 0;
	gc_wrap_mode = 1;
	gc_relative_origin = 0;
	gc_update_color(COLOR_BACKGROUND, FALSE);
	gc_update_color(COLOR_FOREGROUND, TRUE);
}