#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int /*<<< orphan*/ ** uveob_base; int /*<<< orphan*/ * eob_base; void** uvblock_base; void* block_base; void* b_base; } ;
typedef  TYPE_3__ VP9TileData ;
struct TYPE_8__ {TYPE_1__* frames; } ;
struct TYPE_10__ {int bytesperpixel; scalar_t__ block_alloc_using_2pass; int ss_h; int ss_v; int sb_cols; int sb_rows; int cols; int rows; int active_tile_cols; TYPE_2__ s; TYPE_3__* td; } ;
typedef  TYPE_4__ VP9Context ;
typedef  int /*<<< orphan*/  VP9Block ;
struct TYPE_11__ {TYPE_4__* priv_data; } ;
struct TYPE_7__ {scalar_t__ uses_2pass; } ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 size_t CUR_FRAME ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (void*) ; 
 void* av_malloc (int) ; 
 void* av_malloc_array (int,int) ; 
 void* av_mallocz (int) ; 

__attribute__((used)) static int update_block_buffers(AVCodecContext *avctx)
{
    int i;
    VP9Context *s = avctx->priv_data;
    int chroma_blocks, chroma_eobs, bytesperpixel = s->bytesperpixel;
    VP9TileData *td = &s->td[0];

    if (td->b_base && td->block_base && s->block_alloc_using_2pass == s->s.frames[CUR_FRAME].uses_2pass)
        return 0;

    av_free(td->b_base);
    av_free(td->block_base);
    chroma_blocks = 64 * 64 >> (s->ss_h + s->ss_v);
    chroma_eobs   = 16 * 16 >> (s->ss_h + s->ss_v);
    if (s->s.frames[CUR_FRAME].uses_2pass) {
        int sbs = s->sb_cols * s->sb_rows;

        td->b_base = av_malloc_array(s->cols * s->rows, sizeof(VP9Block));
        td->block_base = av_mallocz(((64 * 64 + 2 * chroma_blocks) * bytesperpixel * sizeof(int16_t) +
                                    16 * 16 + 2 * chroma_eobs) * sbs);
        if (!td->b_base || !td->block_base)
            return AVERROR(ENOMEM);
        td->uvblock_base[0] = td->block_base + sbs * 64 * 64 * bytesperpixel;
        td->uvblock_base[1] = td->uvblock_base[0] + sbs * chroma_blocks * bytesperpixel;
        td->eob_base = (uint8_t *) (td->uvblock_base[1] + sbs * chroma_blocks * bytesperpixel);
        td->uveob_base[0] = td->eob_base + 16 * 16 * sbs;
        td->uveob_base[1] = td->uveob_base[0] + chroma_eobs * sbs;
    } else {
        for (i = 1; i < s->active_tile_cols; i++) {
            if (s->td[i].b_base && s->td[i].block_base) {
                av_free(s->td[i].b_base);
                av_free(s->td[i].block_base);
            }
        }
        for (i = 0; i < s->active_tile_cols; i++) {
            s->td[i].b_base = av_malloc(sizeof(VP9Block));
            s->td[i].block_base = av_mallocz((64 * 64 + 2 * chroma_blocks) * bytesperpixel * sizeof(int16_t) +
                                       16 * 16 + 2 * chroma_eobs);
            if (!s->td[i].b_base || !s->td[i].block_base)
                return AVERROR(ENOMEM);
            s->td[i].uvblock_base[0] = s->td[i].block_base + 64 * 64 * bytesperpixel;
            s->td[i].uvblock_base[1] = s->td[i].uvblock_base[0] + chroma_blocks * bytesperpixel;
            s->td[i].eob_base = (uint8_t *) (s->td[i].uvblock_base[1] + chroma_blocks * bytesperpixel);
            s->td[i].uveob_base[0] = s->td[i].eob_base + 16 * 16;
            s->td[i].uveob_base[1] = s->td[i].uveob_base[0] + chroma_eobs;
        }
    }
    s->block_alloc_using_2pass = s->s.frames[CUR_FRAME].uses_2pass;

    return 0;
}