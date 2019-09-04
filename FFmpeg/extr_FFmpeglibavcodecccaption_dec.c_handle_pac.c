#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct Screen {int dummy; } ;
typedef  int int8_t ;
struct TYPE_6__ {int cursor_row; scalar_t__ cursor_column; int /*<<< orphan*/  cursor_charset; void* cursor_font; void* cursor_color; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  CCSET_BASIC_AMERICAN ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct Screen* get_writing_screen (TYPE_1__*) ; 
 void*** pac2_attribs ; 
 int /*<<< orphan*/  write_char (TYPE_1__*,struct Screen*,char) ; 

__attribute__((used)) static void handle_pac(CCaptionSubContext *ctx, uint8_t hi, uint8_t lo)
{
    static const int8_t row_map[] = {
        11, -1, 1, 2, 3, 4, 12, 13, 14, 15, 5, 6, 7, 8, 9, 10
    };
    const int index = ( (hi<<1) & 0x0e) | ( (lo>>5) & 0x01 );
    struct Screen *screen = get_writing_screen(ctx);
    int indent, i;

    if (row_map[index] <= 0) {
        av_log(ctx, AV_LOG_DEBUG, "Invalid pac index encountered\n");
        return;
    }

    lo &= 0x1f;

    ctx->cursor_row = row_map[index] - 1;
    ctx->cursor_color =  pac2_attribs[lo][0];
    ctx->cursor_font = pac2_attribs[lo][1];
    ctx->cursor_charset = CCSET_BASIC_AMERICAN;
    ctx->cursor_column = 0;
    indent = pac2_attribs[lo][2];
    for (i = 0; i < indent; i++) {
        write_char(ctx, screen, ' ');
    }
}