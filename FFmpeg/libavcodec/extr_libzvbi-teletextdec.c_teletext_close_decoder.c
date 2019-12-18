#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_pages; int last_pgno; int last_ass_alignment; scalar_t__ readorder; int /*<<< orphan*/  subtitle_map; int /*<<< orphan*/  pts; int /*<<< orphan*/ * vbi; TYPE_5__* pages; int /*<<< orphan*/  lines_processed; } ;
typedef  TYPE_1__ TeletextContext ;
struct TYPE_8__ {int /*<<< orphan*/  sub_rect; } ;
struct TYPE_7__ {int flags2; TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_RO_FLUSH_NOOP ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  subtitle_rect_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbi_decoder_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int teletext_close_decoder(AVCodecContext *avctx)
{
    TeletextContext *ctx = avctx->priv_data;

    ff_dlog(avctx, "lines_total=%u\n", ctx->lines_processed);
    while (ctx->nb_pages)
        subtitle_rect_free(&ctx->pages[--ctx->nb_pages].sub_rect);
    av_freep(&ctx->pages);

    vbi_decoder_delete(ctx->vbi);
    ctx->vbi = NULL;
    ctx->pts = AV_NOPTS_VALUE;
    ctx->last_pgno = -1;
    ctx->last_ass_alignment = 2;
    memset(ctx->subtitle_map, 0, sizeof(ctx->subtitle_map));
    if (!(avctx->flags2 & AV_CODEC_FLAG2_RO_FLUSH_NOOP))
        ctx->readorder = 0;
    return 0;
}