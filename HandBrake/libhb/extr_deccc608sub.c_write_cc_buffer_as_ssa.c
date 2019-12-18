#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {double num; double den; } ;
struct s_write {int enc_buffer_used; int height; int* crop; int width; scalar_t__* enc_buffer; int line; int clear_sub_needed; int /*<<< orphan*/  list; TYPE_3__* data608; TYPE_1__ par; int /*<<< orphan*/  prev_font_color; int /*<<< orphan*/  prev_font_style; } ;
struct eia608_screen {scalar_t__ dirty; int /*<<< orphan*/ * characters; scalar_t__* row_used; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  scr_sequence; scalar_t__ stop; scalar_t__ start; int /*<<< orphan*/  flags; void* frametype; } ;
struct TYPE_10__ {TYPE_2__ s; scalar_t__ data; } ;
typedef  TYPE_4__ hb_buffer_t ;
struct TYPE_9__ {scalar_t__ current_visible_start_ms; int ssa_counter; int /*<<< orphan*/  current_visible_scr_sequence; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  COL_WHITE ; 
 int /*<<< orphan*/  FONT_REGULAR ; 
 int /*<<< orphan*/  HB_BUF_FLAG_EOS ; 
 void* HB_FRAME_SUBTITLE ; 
 int SSA_PREAMBLE_LEN ; 
 scalar_t__ debug_608 ; 
 int encode_line (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_limit_characters (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_decoder_line_encoded (struct s_write*,scalar_t__*,int,struct eia608_screen*) ; 
 TYPE_4__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 char* hb_strdup_printf (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int stuff_space (scalar_t__*,int) ; 
 scalar_t__ subs_delay ; 

__attribute__((used)) static int write_cc_buffer_as_ssa(struct eia608_screen *data,
                                  struct s_write *wb)
{
    int wrote_something = 0;
    int i;
    int64_t ms_start = wb->data608->current_visible_start_ms;
    //int64_t ms_end = wb->last_pts + subs_delay;

    ms_start += subs_delay;
    if (ms_start<0) // Drop screens that because of subs_delay start too early
        return 0;

    if (debug_608)
    {
        char timeline[128];
        wb->data608->ssa_counter++;
        sprintf (timeline,"%u\r\n",wb->data608->ssa_counter);

        hb_log ("\n- - - SSA caption - - -\n");
        hb_log ("%s", timeline);
    }

    /*
     * Write all the lines into enc_buffer, and then write that out at the end
     * ensure that we only have two lines, insert a newline after the first one,
     * and have a big bottom line (strip spaces from any joined lines).
     */
    int rows = 0, columns = 0;
    int min_row = 15, max_row = 0;
    int min_col = 41, max_col = 0;
    for (i = 0; i < 15; i++)
    {
        if (data->row_used[i])
        {
            int first, last;

            rows++;
            find_limit_characters(data->characters[i], &first, &last);
            if (last - first + 1 > columns)
                columns = last - first + 1;
            if (min_col > first)
                min_col = first;
            if (min_row > i)
                min_row = i;
            if (max_col < last)
                max_col = last;
            if (max_row < i)
                max_row = i;
        }
    }

    wb->prev_font_style = FONT_REGULAR;
    wb->prev_font_color = COL_WHITE;
    wb->enc_buffer_used = 0;

    int cropped_width, cropped_height, font_size;
    int cell_width, cell_height;
    int safe_x, safe_y;
    int min_safe_x, min_safe_y;
    double aspect;

    cropped_height = wb->height - wb->crop[0] - wb->crop[1];
    cropped_width = wb->width - wb->crop[2] - wb->crop[3];
    aspect = (double)wb->width * wb->par.num /
                    (wb->height * wb->par.den);

    // CC grid is 16 rows by 32 columns (for 4:3 video)
    // Our SSA resolution is the title resolution
    // Translate CC grid to SSA coordinates
    // The numbers are tweaked to keep things off the very
    // edges of the screen and in the "safe" zone
    int screen_columns = 32;
    if (aspect >= 1.6)
    {
        // If the display aspect is close to or greater than 16:9
        // then width of screen is 42 columns (see CEA-708)
        screen_columns = 42;
    }
    font_size = wb->height * .8 * .08;

    safe_x = 0.1 * wb->width;
    safe_y = 0.1 * wb->height;
    min_safe_x = 0.025 * cropped_width;
    min_safe_y = 0.025 * cropped_height;
    cell_height = (wb->height - 2 * safe_y) / 16;
    cell_width  = (wb->width  - 2 * safe_x) / screen_columns;

    char *pos;
    int y, x, top;
    int col = min_col;
    if (aspect >= 1.6)
    {
        // If the display aspect is close to or greater than 16:9
        // center the CC in about a 4:3 region
        col += 5;
    }
    y = cell_height * (min_row + 1 + rows) + safe_y - wb->crop[0];
    x = cell_width * col + safe_x - wb->crop[2];
    top = y - rows * font_size;

    if (top < min_safe_y)
        y = (rows * font_size) + min_safe_y;
    if (y > cropped_height - min_safe_y)
        y = cropped_height - min_safe_y;
    if (x + columns * cell_width > cropped_width - min_safe_x)
        x = cropped_width - columns * cell_width - min_safe_x;
    if (x < min_safe_x)
        x = min_safe_x;
    pos = hb_strdup_printf("{\\an1\\pos(%d,%d)}", x, y);

    int line = 1;
    for (i = 0; i < 15; i++)
    {
        if (data->row_used[i])
        {
            int first, last;
            // Get position for this CC
            find_limit_characters(data->characters[i], &first, &last);

            /*
             * The intention was to use a newline but QT doesn't like it,
             * old code still here just in case..
             */
            int space = first - min_col;
            if (line == 1) {
                wb->enc_buffer_used += encode_line(
                        wb->enc_buffer + wb->enc_buffer_used, (uint8_t*)pos);
                wb->enc_buffer_used += stuff_space(
                        wb->enc_buffer + wb->enc_buffer_used, space);
                wb->enc_buffer_used += get_decoder_line_encoded(wb,
                        wb->enc_buffer + wb->enc_buffer_used, i, data);
                line = 2;
            } else {
                wb->enc_buffer_used += encode_line(
                        wb->enc_buffer + wb->enc_buffer_used, (uint8_t*)"\\N");
                wb->enc_buffer_used += stuff_space(
                        wb->enc_buffer + wb->enc_buffer_used, space);
                wb->enc_buffer_used += get_decoder_line_encoded(wb,
                        wb->enc_buffer + wb->enc_buffer_used, i, data);
            }
        }
    }
    free(pos);
    if (wb->enc_buffer_used && wb->enc_buffer[0] != 0 && data->dirty)
    {
        hb_buffer_t *buffer;
        int len;

        // bump past null terminator
        wb->enc_buffer_used++;
        buffer = hb_buffer_init(wb->enc_buffer_used + SSA_PREAMBLE_LEN);
        buffer->s.frametype = HB_FRAME_SUBTITLE;
        buffer->s.start = ms_start;
        buffer->s.stop = AV_NOPTS_VALUE;
        buffer->s.scr_sequence = wb->data608->current_visible_scr_sequence;
        sprintf((char*)buffer->data, "%d,,Default,,0,0,0,,", ++wb->line);
        len = strlen((char*)buffer->data);
        memcpy(buffer->data + len, wb->enc_buffer, wb->enc_buffer_used);
        hb_buffer_list_append(&wb->list, buffer);
        wrote_something=1;
        wb->clear_sub_needed = 1;
    }
    else if (wb->clear_sub_needed)
    {
        hb_buffer_t *buffer = hb_buffer_init(0);
        buffer->s.frametype = HB_FRAME_SUBTITLE;
        buffer->s.flags     = HB_BUF_FLAG_EOS;
        buffer->s.start     = ms_start;
        buffer->s.stop      = ms_start;
        buffer->s.scr_sequence = wb->data608->current_visible_scr_sequence;
        hb_buffer_list_append(&wb->list, buffer);
        wb->clear_sub_needed = 0;
    }
    if (debug_608)
    {
        hb_log ("- - - - - - - - - - - -\r\n");
    }
    return wrote_something;
}