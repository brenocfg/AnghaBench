#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int line_pos; int rec_pos; int /*<<< orphan*/  fp; scalar_t__ blank_count; } ;
typedef  TYPE_1__ OVERLAY_HELP_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 
 char* overlay_help_field_data (TYPE_1__*) ; 
 scalar_t__ overlay_help_find_field (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

int overlay_help_find(OVERLAY_HELP_STATE_T *state, const char *name)
{
    state->line_pos = -1;
    state->rec_pos = -1;
    state->blank_count = 0;

    fseek(state->fp, 0, SEEK_SET);

    while (overlay_help_find_field(state, "Name"))
    {
        const char *overlay = overlay_help_field_data(state);
        if (overlay && (strcmp(overlay, name) == 0))
        {
            state->rec_pos = (long)ftell(state->fp);
            return 1;
        }
    }

    return 0;
}