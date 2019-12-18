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
struct TYPE_3__ {int line_pos; int line_len; char* line_buf; scalar_t__ rec_pos; int blank_count; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ OVERLAY_HELP_STATE_T ;

/* Variables and functions */
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int overlay_help_get_line(OVERLAY_HELP_STATE_T *state)
{
    int line_len;

    if (state->line_pos >= 0)
	return state->line_len;

get_next_line:
    state->line_buf[sizeof(state->line_buf) - 1] = ' ';
    line_len = -1;
    if (fgets(state->line_buf, sizeof(state->line_buf), state->fp))
    {
	// Check for overflow

	// Strip the newline
	line_len = strlen(state->line_buf);
	if (line_len && (state->line_buf[line_len - 1] == '\n'))
	{
	    line_len--;
	    state->line_buf[line_len] = '\0';
	}
    }

    if (state->rec_pos >= 0)
    {
	if (line_len == 0)
	{
	    state->blank_count++;
	    if (state->blank_count >= 2)
		return -1;
	    state->line_pos = 0;
	    goto get_next_line;
	}
	else if (state->blank_count)
	{
	    /* Return a single blank line now - the non-empty line will be
	       returned next time */
	    state->blank_count = 0;
	    return 0;
	}
    }

    state->line_len = line_len;
    state->line_pos = (line_len >= 0) ? 0 : -1;
    return line_len;
}