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
typedef  int uint8_t ;
struct Screen {int /*<<< orphan*/  row_used; } ;
struct TYPE_5__ {int /*<<< orphan*/  cursor_row; void* cursor_font; void* cursor_color; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Screen* get_writing_screen (TYPE_1__*) ; 
 void*** pac2_attribs ; 
 int /*<<< orphan*/  write_char (TYPE_1__*,struct Screen*,char) ; 

__attribute__((used)) static void handle_textattr(CCaptionSubContext *ctx, uint8_t hi, uint8_t lo)
{
    int i = lo - 0x20;
    struct Screen *screen = get_writing_screen(ctx);

    if (i >= 32)
        return;

    ctx->cursor_color = pac2_attribs[i][0];
    ctx->cursor_font = pac2_attribs[i][1];

    SET_FLAG(screen->row_used, ctx->cursor_row);
    write_char(ctx, screen, ' ');
}