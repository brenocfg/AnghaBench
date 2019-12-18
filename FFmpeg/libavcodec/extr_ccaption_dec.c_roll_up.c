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
struct Screen {scalar_t__ row_used; int /*<<< orphan*/ * charsets; int /*<<< orphan*/ * fonts; int /*<<< orphan*/ * colors; int /*<<< orphan*/ * characters; } ;
struct TYPE_4__ {scalar_t__ mode; int cursor_row; int /*<<< orphan*/  rollup; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 scalar_t__ CCMODE_TEXT ; 
 scalar_t__ CHECK_FLAG (scalar_t__,int const) ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCREEN_COLUMNS ; 
 int SCREEN_ROWS ; 
 int /*<<< orphan*/  SET_FLAG (scalar_t__,int const) ; 
 int /*<<< orphan*/  UNSET_FLAG (scalar_t__,int) ; 
 struct Screen* get_writing_screen (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void roll_up(CCaptionSubContext *ctx)
{
    struct Screen *screen;
    int i, keep_lines;

    if (ctx->mode == CCMODE_TEXT)
        return;

    screen = get_writing_screen(ctx);

    /* +1 signify cursor_row starts from 0
     * Can't keep lines less then row cursor pos
     */
    keep_lines = FFMIN(ctx->cursor_row + 1, ctx->rollup);

    for (i = 0; i < SCREEN_ROWS; i++) {
        if (i > ctx->cursor_row - keep_lines && i <= ctx->cursor_row)
            continue;
        UNSET_FLAG(screen->row_used, i);
    }

    for (i = 0; i < keep_lines && screen->row_used; i++) {
        const int i_row = ctx->cursor_row - keep_lines + i + 1;

        memcpy(screen->characters[i_row], screen->characters[i_row+1], SCREEN_COLUMNS);
        memcpy(screen->colors[i_row], screen->colors[i_row+1], SCREEN_COLUMNS);
        memcpy(screen->fonts[i_row], screen->fonts[i_row+1], SCREEN_COLUMNS);
        memcpy(screen->charsets[i_row], screen->charsets[i_row+1], SCREEN_COLUMNS);
        if (CHECK_FLAG(screen->row_used, i_row + 1))
            SET_FLAG(screen->row_used, i_row);
    }

    UNSET_FLAG(screen->row_used, ctx->cursor_row);
}