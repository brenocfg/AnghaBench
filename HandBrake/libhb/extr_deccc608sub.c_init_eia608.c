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
struct eia608 {int visible_buffer; int channel; int rollup_base_row; int /*<<< orphan*/  font; int /*<<< orphan*/  color; scalar_t__ screenfuls_counter; scalar_t__ ssa_counter; scalar_t__ current_visible_start_ms; int /*<<< orphan*/  mode; scalar_t__ last_c2; scalar_t__ last_c1; int /*<<< orphan*/  buffer2; int /*<<< orphan*/  buffer1; scalar_t__ cursor_row; scalar_t__ cursor_column; } ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_REGULAR ; 
 int /*<<< orphan*/  MODE_POPUP ; 
 int /*<<< orphan*/  clear_eia608_cc_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_color ; 

__attribute__((used)) static void init_eia608 (struct eia608 *data)
{
    data->cursor_column = 0;
    data->cursor_row = 0;
    clear_eia608_cc_buffer (&data->buffer1);
    clear_eia608_cc_buffer (&data->buffer2);
    data->visible_buffer = 1;
    data->last_c1 = 0;
    data->last_c2 = 0;
    data->mode = MODE_POPUP;
    data->current_visible_start_ms = 0;
    data->ssa_counter = 0;
    data->screenfuls_counter = 0;
    data->channel = 1;
    data->color = default_color;
    data->font = FONT_REGULAR;
    data->rollup_base_row = 14;
}