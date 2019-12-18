#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int end_of_field; int line_len; int line_pos; char* line_buf; } ;
typedef  TYPE_1__ OVERLAY_HELP_STATE_T ;

/* Variables and functions */
 int OVERLAY_HELP_INDENT ; 
 int overlay_help_get_line (TYPE_1__*) ; 

const char *overlay_help_field_data(OVERLAY_HELP_STATE_T *state)
{
    int line_len, pos;

    if (state->end_of_field)
        return NULL;

    line_len = state->line_len;

    if ((state->line_pos < 0) ||
        (state->line_pos >= line_len))
    {
        line_len = overlay_help_get_line(state);

        /* Fields end at the start of the next field or the end of the record */
        if ((line_len < 0) || (state->line_buf[0] != ' '))
        {
            state->end_of_field = 1;
            return NULL;
        }

        if (line_len == 0)
            return "";
    }

    /* Return field data starting at OVERLAY_HELP_INDENT, if there is any */
    pos = line_len;
    if (pos > OVERLAY_HELP_INDENT)
        pos = OVERLAY_HELP_INDENT;

    state->line_pos = -1;
    return &state->line_buf[pos];
}