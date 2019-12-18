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
struct TYPE_4__ {int line_pos; int rec_pos; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ OVERLAY_HELP_STATE_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

OVERLAY_HELP_STATE_T *overlay_help_open(const char *helpfile)
{
    OVERLAY_HELP_STATE_T *state = NULL;
    FILE *fp = fopen(helpfile, "r");
    if (fp)
    {
        state = calloc(1, sizeof(OVERLAY_HELP_STATE_T));
        if (!state)
                fatal_error("Out of memory");
        state->fp = fp;
        state->line_pos = -1;
        state->rec_pos = -1;
    }

    return state;
}