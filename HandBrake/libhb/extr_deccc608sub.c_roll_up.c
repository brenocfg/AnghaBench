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
struct s_write {TYPE_1__* data608; } ;
struct eia608_screen {int dirty; scalar_t__* row_used; scalar_t__** characters; scalar_t__** fonts; scalar_t__** colors; } ;
struct TYPE_2__ {int mode; int cursor_row; } ;

/* Variables and functions */
 int CC608_SCREEN_WIDTH ; 
 char COL_WHITE ; 
 char FONT_REGULAR ; 
#define  MODE_ROLLUP_2 130 
#define  MODE_ROLLUP_3 129 
#define  MODE_ROLLUP_4 128 
 scalar_t__ debug_608 ; 
 struct eia608_screen* get_current_visible_buffer (struct s_write*) ; 
 int /*<<< orphan*/  hb_log (char*,int,int,...) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,char,int) ; 

__attribute__((used)) static void roll_up(struct s_write *wb)
{
    struct eia608_screen *use_buffer;
    int i, j;

    use_buffer = get_current_visible_buffer(wb);
    int keep_lines;
    switch (wb->data608->mode)
    {
        case MODE_ROLLUP_2:
            keep_lines = 2;
            break;
        case MODE_ROLLUP_3:
            keep_lines = 3;
            break;
        case MODE_ROLLUP_4:
            keep_lines = 4;
            break;
        default: // Shouldn't happen
            keep_lines = 0;
            break;
    }
    int firstrow = -1, lastrow = -1;
    // Look for the last line used
    int rows_now = 0; // Number of rows in use right now
    for (i = 0; i < 15; i++)
    {
        if (use_buffer->row_used[i])
        {
            rows_now++;
            if (firstrow == -1)
                firstrow = i;
            lastrow = i;
        }
    }

    if (debug_608)
        hb_log ("\rIn roll-up: %d lines used, first: %d, last: %d\n", rows_now, firstrow, lastrow);

    if (lastrow==-1) // Empty screen, nothing to rollup
        return;

    for (j = lastrow - keep_lines + 1; j < lastrow; j++)
    {
        if (j >= 0)
        {
            memcpy(use_buffer->characters[j], use_buffer->characters[j+1], CC608_SCREEN_WIDTH+1);
            memcpy(use_buffer->colors[j], use_buffer->colors[j+1], CC608_SCREEN_WIDTH+1);
            memcpy(use_buffer->fonts[j], use_buffer->fonts[j+1], CC608_SCREEN_WIDTH+1);
            use_buffer->row_used[j] = use_buffer->row_used[j+1];
        }
    }
    for (j = 0; j < (1 + wb->data608->cursor_row - keep_lines); j++)
    {
        memset(use_buffer->characters[j], ' ', CC608_SCREEN_WIDTH);
        memset(use_buffer->colors[j], COL_WHITE, CC608_SCREEN_WIDTH);
        memset(use_buffer->fonts[j], FONT_REGULAR, CC608_SCREEN_WIDTH);
        use_buffer->characters[j][CC608_SCREEN_WIDTH] = 0;
        use_buffer->row_used[j] = 0;
    }
    memset(use_buffer->characters[lastrow], ' ', CC608_SCREEN_WIDTH);
    memset(use_buffer->colors[lastrow], COL_WHITE, CC608_SCREEN_WIDTH);
    memset(use_buffer->fonts[lastrow], FONT_REGULAR, CC608_SCREEN_WIDTH);

    use_buffer->characters[lastrow][CC608_SCREEN_WIDTH] = 0;
    use_buffer->row_used[lastrow] = 0;

    // Sanity check
    rows_now = 0;
    for (i = 0; i < 15; i++)
        if (use_buffer->row_used[i])
            rows_now++;
    if (rows_now > keep_lines)
        hb_log ("Bug in roll_up, should have %d lines but I have %d.\n",
            keep_lines, rows_now);
    use_buffer->dirty = 1;
}