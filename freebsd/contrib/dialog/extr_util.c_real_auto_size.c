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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_4__ {double aspect_ratio; int text_height; int text_width; } ;
struct TYPE_3__ {int begin_x; int begin_y; scalar_t__ begin_set; } ;

/* Variables and functions */
 int MARGIN ; 
 int MAX (int,int) ; 
 int SCOLS ; 
 scalar_t__ SHADOW_COLS ; 
 int SLINES ; 
 int /*<<< orphan*/  auto_size_preformatted (char const*,int*,int*) ; 
 TYPE_2__ dialog_state ; 
 TYPE_1__ dialog_vars ; 
 int dlg_count_columns (char const*) ; 
 double dlg_count_real_columns (char const*) ; 
 int /*<<< orphan*/  justify_text (int /*<<< orphan*/ *,char const*,int,int,int*,int*) ; 
 int longest_word (char const*) ; 
 double sqrt (double) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static void
real_auto_size(const char *title,
	       const char *prompt,
	       int *height, int *width,
	       int boxlines, int mincols)
{
    int x = (dialog_vars.begin_set ? dialog_vars.begin_x : 2);
    int y = (dialog_vars.begin_set ? dialog_vars.begin_y : 1);
    int title_length = title ? dlg_count_columns(title) : 0;
    int high;
    int wide;
    int save_high = *height;
    int save_wide = *width;
    int max_high;
    int max_wide;

    if (prompt == 0) {
	if (*height == 0)
	    *height = -1;
	if (*width == 0)
	    *width = -1;
    }

    max_high = (*height < 0);
    max_wide = (*width < 0);

    if (*height > 0) {
	high = *height;
    } else {
	high = SLINES - y;
    }

    if (*width <= 0) {
	if (prompt != 0) {
	    wide = MAX(title_length, mincols);
	    if (strchr(prompt, '\n') == 0) {
		double val = (dialog_state.aspect_ratio *
			      dlg_count_real_columns(prompt));
		double xxx = sqrt(val);
		int tmp = (int) xxx;
		wide = MAX(wide, tmp);
		wide = MAX(wide, longest_word(prompt));
		justify_text((WINDOW *) 0, prompt, high, wide, height, width);
	    } else {
		auto_size_preformatted(prompt, height, width);
	    }
	} else {
	    wide = SCOLS - x;
	    justify_text((WINDOW *) 0, prompt, high, wide, height, width);
	}
    }

    if (*width < title_length) {
	justify_text((WINDOW *) 0, prompt, high, title_length, height, width);
	*width = title_length;
    }

    dialog_state.text_height = *height;
    dialog_state.text_width = *width;

    if (*width < mincols && save_wide == 0)
	*width = mincols;
    if (prompt != 0) {
	*width += ((2 * MARGIN) + SHADOW_COLS);
	*height += boxlines + (2 * MARGIN);
    }

    if (save_high > 0)
	*height = save_high;
    if (save_wide > 0)
	*width = save_wide;

    if (max_high)
	*height = SLINES - (dialog_vars.begin_set ? dialog_vars.begin_y : 0);
    if (max_wide)
	*width = SCOLS - (dialog_vars.begin_set ? dialog_vars.begin_x : 0);
}