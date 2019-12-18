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
struct s_write {scalar_t__ new_channel; int rollup_cr; TYPE_1__* data608; int /*<<< orphan*/  last_scr_sequence; int /*<<< orphan*/  last_pts; } ;
struct eia608_screen {char** characters; int dirty; } ;
typedef  enum command_code { ____Placeholder_command_code } command_code ;
struct TYPE_2__ {scalar_t__ channel; size_t cursor_column; size_t cursor_row; int rollup_base_row; void* font; void* color; int /*<<< orphan*/  mode; int /*<<< orphan*/  screenfuls_counter; int /*<<< orphan*/  current_visible_scr_sequence; int /*<<< orphan*/  current_visible_start_ms; } ;

/* Variables and functions */
#define  COM_BACKSPACE 140 
#define  COM_CARRIAGERETURN 139 
#define  COM_ENDOFCAPTION 138 
#define  COM_ERASEDISPLAYEDMEMORY 137 
#define  COM_ERASENONDISPLAYEDMEMORY 136 
#define  COM_RESUMECAPTIONLOADING 135 
#define  COM_RESUMETEXTDISPLAY 134 
#define  COM_ROLLUP2 133 
#define  COM_ROLLUP3 132 
#define  COM_ROLLUP4 131 
#define  COM_TABOFFSET1 130 
#define  COM_TABOFFSET2 129 
#define  COM_TABOFFSET3 128 
 int COM_UNKNOWN ; 
 void* FONT_REGULAR ; 
 int /*<<< orphan*/  MODE_POPUP ; 
 int /*<<< orphan*/  MODE_ROLLUP_2 ; 
 int /*<<< orphan*/  MODE_ROLLUP_3 ; 
 int /*<<< orphan*/  MODE_ROLLUP_4 ; 
 int /*<<< orphan*/  MODE_TEXT ; 
 scalar_t__ cc_channel ; 
 int /*<<< orphan*/ * command_type ; 
 scalar_t__ debug_608 ; 
 void* default_color ; 
 int /*<<< orphan*/  erase_memory (struct s_write*,int) ; 
 struct eia608_screen* get_current_visible_buffer (struct s_write*) ; 
 struct eia608_screen* get_writing_buffer (struct s_write*) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  is_current_row_empty (struct s_write*) ; 
 int /*<<< orphan*/  move_roll_up (struct s_write*,int) ; 
 int /*<<< orphan*/  roll_up (struct s_write*) ; 
 int /*<<< orphan*/  swap_visible_buffer (struct s_write*) ; 
 int /*<<< orphan*/  write_cc_buffer (struct s_write*) ; 

__attribute__((used)) static void handle_command(unsigned char c1, const unsigned char c2,
                           struct s_write *wb)
{
    // Handle channel change
    wb->data608->channel=wb->new_channel;
    if (wb->data608->channel!=cc_channel)
        return;

    enum command_code command = COM_UNKNOWN;
    if (c1==0x15)
        c1=0x14;
    if ((c1==0x14 || c1==0x1C) && c2==0x2C)
        command = COM_ERASEDISPLAYEDMEMORY;
    if ((c1==0x14 || c1==0x1C) && c2==0x20)
        command = COM_RESUMECAPTIONLOADING;
    if ((c1==0x14 || c1==0x1C) && c2==0x2F)
        command = COM_ENDOFCAPTION;
    if ((c1==0x17 || c1==0x1F) && c2==0x21)
        command = COM_TABOFFSET1;
    if ((c1==0x17 || c1==0x1F) && c2==0x22)
        command = COM_TABOFFSET2;
    if ((c1==0x17 || c1==0x1F) && c2==0x23)
        command = COM_TABOFFSET3;
    if ((c1==0x14 || c1==0x1C) && c2==0x25)
        command = COM_ROLLUP2;
    if ((c1==0x14 || c1==0x1C) && c2==0x26)
        command = COM_ROLLUP3;
    if ((c1==0x14 || c1==0x1C) && c2==0x27)
        command = COM_ROLLUP4;
    if ((c1==0x14 || c1==0x1C) && c2==0x2D)
        command = COM_CARRIAGERETURN;
    if ((c1==0x14 || c1==0x1C) && c2==0x2E)
        command = COM_ERASENONDISPLAYEDMEMORY;
    if ((c1==0x14 || c1==0x1C) && c2==0x21)
        command = COM_BACKSPACE;
    if ((c1==0x14 || c1==0x1C) && c2==0x2b)
        command = COM_RESUMETEXTDISPLAY;
    if (debug_608)
    {
        hb_log ("\rCommand: %02X %02X (%s)\n",c1,c2,command_type[command]);
    }
    switch (command)
    {
        case COM_BACKSPACE:
            if (wb->data608->cursor_column>0)
            {
                struct eia608_screen *data;
                data = get_writing_buffer(wb);
                if (data != NULL)
                {
                    wb->data608->cursor_column--;
                    data->characters[wb->data608->cursor_row][wb->data608->cursor_column] = ' ';
                    data->dirty = 1;
                }
            }
            break;
        case COM_TABOFFSET1:
            if (wb->data608->cursor_column<31)
                wb->data608->cursor_column++;
            break;
        case COM_TABOFFSET2:
            wb->data608->cursor_column+=2;
            if (wb->data608->cursor_column>31)
                wb->data608->cursor_column=31;
            break;
        case COM_TABOFFSET3:
            wb->data608->cursor_column+=3;
            if (wb->data608->cursor_column>31)
                wb->data608->cursor_column=31;
            break;
        case COM_RESUMECAPTIONLOADING:
            wb->data608->mode=MODE_POPUP;
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            break;
        case COM_RESUMETEXTDISPLAY:
            wb->data608->mode=MODE_TEXT;
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            break;
        case COM_ROLLUP2:
            if (wb->data608->rollup_base_row + 1 < 2)
            {
                move_roll_up(wb, 1);
                wb->data608->rollup_base_row = 1;
            }
            if (wb->data608->mode==MODE_POPUP)
            {
                swap_visible_buffer(wb);
                if (write_cc_buffer(wb))
                    wb->data608->screenfuls_counter++;
                erase_memory (wb, 1);
            }
            wb->data608->color=default_color;
            wb->data608->font=FONT_REGULAR;
            if (wb->data608->mode==MODE_ROLLUP_2 && !is_current_row_empty(wb))
            {
                if (debug_608)
                    hb_log ("Two RU2, current line not empty. Simulating a CR\n");
                handle_command(0x14, 0x2D, wb);
                wb->rollup_cr = 1;
            }
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            wb->data608->mode=MODE_ROLLUP_2;
            erase_memory (wb, 0);
            wb->data608->cursor_column = 0;
            wb->data608->cursor_row = wb->data608->rollup_base_row;
            break;
        case COM_ROLLUP3:
            if (wb->data608->rollup_base_row + 1 < 3)
            {
                move_roll_up(wb, 2);
                wb->data608->rollup_base_row = 2;
            }
            if (wb->data608->mode==MODE_POPUP)
            {
                if (write_cc_buffer(wb))
                    wb->data608->screenfuls_counter++;
                erase_memory (wb, 1);
            }
            wb->data608->color=default_color;
            wb->data608->font=FONT_REGULAR;
            if (wb->data608->mode==MODE_ROLLUP_3 && !is_current_row_empty(wb))
            {
                if (debug_608)
                    hb_log ("Two RU3, current line not empty. Simulating a CR\n");
                handle_command(0x14, 0x2D, wb);
                wb->rollup_cr = 1;
            }
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            wb->data608->mode=MODE_ROLLUP_3;
            erase_memory (wb, 0);
            wb->data608->cursor_column = 0;
            wb->data608->cursor_row = wb->data608->rollup_base_row;
            break;
        case COM_ROLLUP4:
            if (wb->data608->rollup_base_row + 1 < 4)
            {
                move_roll_up(wb, 3);
                wb->data608->rollup_base_row = 3;
            }
            if (wb->data608->mode==MODE_POPUP)
            {
                if (write_cc_buffer(wb))
                    wb->data608->screenfuls_counter++;
                erase_memory (wb, 1);
            }
            wb->data608->color=default_color;
            wb->data608->font=FONT_REGULAR;
            if (wb->data608->mode==MODE_ROLLUP_4 && !is_current_row_empty(wb))
            {
                if (debug_608)
                    hb_log ("Two RU4, current line not empty. Simulating a CR\n");
                handle_command(0x14, 0x2D, wb);
                wb->rollup_cr = 1;
            }
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            wb->data608->mode = MODE_ROLLUP_4;
            wb->data608->cursor_column = 0;
            wb->data608->cursor_row = wb->data608->rollup_base_row;
            erase_memory (wb, 0);
            break;
        case COM_CARRIAGERETURN:
            // In transcript mode, CR doesn't write the whole screen, to avoid
            // repeated lines.

            // Skip initial CR if rollup has already done it
            if (wb->rollup_cr && is_current_row_empty(wb))
            {
                wb->rollup_cr = 0;
                wb->data608->current_visible_start_ms = wb->last_pts;
                wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
                break;
            }
            if (write_cc_buffer(wb))
                wb->data608->screenfuls_counter++;
            roll_up(wb);
            wb->data608->cursor_column = 0;
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            break;
        case COM_ERASENONDISPLAYEDMEMORY:
            erase_memory (wb,0);
            break;
        case COM_ERASEDISPLAYEDMEMORY:
            // There may be "displayed" rollup data that has not been
            // written to a buffer yet.
            if (wb->data608->mode == MODE_ROLLUP_2 ||
                wb->data608->mode == MODE_ROLLUP_3 ||
                wb->data608->mode == MODE_ROLLUP_4)
            {
                write_cc_buffer(wb);
            }
            erase_memory (wb,1);

            // the last pts is the time to remove the previously
            // displayed CC from the display
            wb->data608->current_visible_start_ms = wb->last_pts;
            wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;

            // Write "clear" subtitle if necessary
            struct eia608_screen *data;
            data = get_current_visible_buffer(wb);
            data->dirty = 1;
            write_cc_buffer(wb);
            break;
        case COM_ENDOFCAPTION: // Switch buffers
            // The currently *visible* buffer is leaving, so now we know it's ending
            // time. Time to actually write it to file.
            if (wb->data608->mode == MODE_POPUP)
            {
                swap_visible_buffer(wb);
                wb->data608->current_visible_start_ms = wb->last_pts;
                wb->data608->current_visible_scr_sequence = wb->last_scr_sequence;
            }
            if (write_cc_buffer(wb))
                wb->data608->screenfuls_counter++;

            if (wb->data608->mode != MODE_POPUP)
                swap_visible_buffer(wb);
            wb->data608->cursor_column = 0;
            wb->data608->cursor_row = 0;
            wb->data608->color=default_color;
            wb->data608->font=FONT_REGULAR;
            break;
        default:
            if (debug_608)
            {
                hb_log ("\rNot yet implemented.\n");
            }
            break;
    }
}