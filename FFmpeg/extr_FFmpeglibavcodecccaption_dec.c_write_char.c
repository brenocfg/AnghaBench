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
typedef  size_t uint8_t ;
struct Screen {char** characters; char** fonts; char** charsets; } ;
struct TYPE_4__ {size_t cursor_column; size_t cursor_row; char cursor_font; char cursor_charset; } ;
typedef  TYPE_1__ CCaptionSubContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 char CCSET_BASIC_AMERICAN ; 
 size_t SCREEN_COLUMNS ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void write_char(CCaptionSubContext *ctx, struct Screen *screen, char ch)
{
    uint8_t col = ctx->cursor_column;
    char *row = screen->characters[ctx->cursor_row];
    char *font = screen->fonts[ctx->cursor_row];
    char *charset = screen->charsets[ctx->cursor_row];

    if (col < SCREEN_COLUMNS) {
        row[col] = ch;
        font[col] = ctx->cursor_font;
        charset[col] = ctx->cursor_charset;
        ctx->cursor_charset = CCSET_BASIC_AMERICAN;
        if (ch) ctx->cursor_column++;
        return;
    }
    /* We have extra space at end only for null character */
    else if (col == SCREEN_COLUMNS && ch == 0) {
        row[col] = ch;
        return;
    }
    else {
        av_log(ctx, AV_LOG_WARNING, "Data Ignored since exceeding screen width\n");
        return;
    }
}