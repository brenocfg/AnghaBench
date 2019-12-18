#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags2; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int rollup; int cursor_row; int /*<<< orphan*/  buffer; scalar_t__ readorder; scalar_t__ buffer_changed; scalar_t__ screen_touched; scalar_t__ last_real_time; scalar_t__ active_screen; scalar_t__ cursor_charset; scalar_t__ cursor_color; scalar_t__ cursor_font; scalar_t__ cursor_column; int /*<<< orphan*/  mode; scalar_t__* prev_cmd; TYPE_1__* screen; } ;
struct TYPE_5__ {scalar_t__ row_used; } ;
typedef  TYPE_2__ CCaptionSubContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_RO_FLUSH_NOOP ; 
 int /*<<< orphan*/  CCMODE_ROLLUP ; 
 int /*<<< orphan*/  av_bprint_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_decoder(AVCodecContext *avctx)
{
    CCaptionSubContext *ctx = avctx->priv_data;
    ctx->screen[0].row_used = 0;
    ctx->screen[1].row_used = 0;
    ctx->prev_cmd[0] = 0;
    ctx->prev_cmd[1] = 0;
    ctx->mode = CCMODE_ROLLUP;
    ctx->rollup = 2;
    ctx->cursor_row = 10;
    ctx->cursor_column = 0;
    ctx->cursor_font = 0;
    ctx->cursor_color = 0;
    ctx->cursor_charset = 0;
    ctx->active_screen = 0;
    ctx->last_real_time = 0;
    ctx->screen_touched = 0;
    ctx->buffer_changed = 0;
    if (!(avctx->flags2 & AV_CODEC_FLAG2_RO_FLUSH_NOOP))
        ctx->readorder = 0;
    av_bprint_clear(&ctx->buffer);
}