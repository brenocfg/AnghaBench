#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
typedef  enum BlockLevel { ____Placeholder_BlockLevel } BlockLevel ;
struct TYPE_13__ {TYPE_6__* b; TYPE_5__* s; } ;
typedef  TYPE_4__ VP9TileData ;
typedef  int /*<<< orphan*/  VP9Filter ;
struct TYPE_12__ {TYPE_2__* frames; } ;
struct TYPE_14__ {int bytesperpixel; int rows; int ss_v; int cols; int ss_h; TYPE_3__ s; } ;
typedef  TYPE_5__ VP9Context ;
struct TYPE_15__ {int bl; scalar_t__ bp; } ;
typedef  TYPE_6__ VP9Block ;
struct TYPE_16__ {int* linesize; } ;
struct TYPE_10__ {TYPE_7__* f; } ;
struct TYPE_11__ {TYPE_1__ tf; } ;
typedef  TYPE_7__ AVFrame ;

/* Variables and functions */
 int BL_8X8 ; 
 size_t CUR_FRAME ; 
 scalar_t__ PARTITION_H ; 
 scalar_t__ PARTITION_V ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  ff_vp9_decode_block (TYPE_4__*,int,int,int /*<<< orphan*/ *,int,int,int,scalar_t__) ; 

__attribute__((used)) static void decode_sb_mem(VP9TileData *td, int row, int col, VP9Filter *lflvl,
                          ptrdiff_t yoff, ptrdiff_t uvoff, enum BlockLevel bl)
{
    const VP9Context *s = td->s;
    VP9Block *b = td->b;
    ptrdiff_t hbs = 4 >> bl;
    AVFrame *f = s->s.frames[CUR_FRAME].tf.f;
    ptrdiff_t y_stride = f->linesize[0], uv_stride = f->linesize[1];
    int bytesperpixel = s->bytesperpixel;

    if (bl == BL_8X8) {
        av_assert2(b->bl == BL_8X8);
        ff_vp9_decode_block(td, row, col, lflvl, yoff, uvoff, b->bl, b->bp);
    } else if (td->b->bl == bl) {
        ff_vp9_decode_block(td, row, col, lflvl, yoff, uvoff, b->bl, b->bp);
        if (b->bp == PARTITION_H && row + hbs < s->rows) {
            yoff  += hbs * 8 * y_stride;
            uvoff += hbs * 8 * uv_stride >> s->ss_v;
            ff_vp9_decode_block(td, row + hbs, col, lflvl, yoff, uvoff, b->bl, b->bp);
        } else if (b->bp == PARTITION_V && col + hbs < s->cols) {
            yoff  += hbs * 8 * bytesperpixel;
            uvoff += hbs * 8 * bytesperpixel >> s->ss_h;
            ff_vp9_decode_block(td, row, col + hbs, lflvl, yoff, uvoff, b->bl, b->bp);
        }
    } else {
        decode_sb_mem(td, row, col, lflvl, yoff, uvoff, bl + 1);
        if (col + hbs < s->cols) { // FIXME why not <=?
            if (row + hbs < s->rows) {
                decode_sb_mem(td, row, col + hbs, lflvl, yoff + 8 * hbs * bytesperpixel,
                              uvoff + (8 * hbs * bytesperpixel >> s->ss_h), bl + 1);
                yoff  += hbs * 8 * y_stride;
                uvoff += hbs * 8 * uv_stride >> s->ss_v;
                decode_sb_mem(td, row + hbs, col, lflvl, yoff, uvoff, bl + 1);
                decode_sb_mem(td, row + hbs, col + hbs, lflvl,
                              yoff + 8 * hbs * bytesperpixel,
                              uvoff + (8 * hbs * bytesperpixel >> s->ss_h), bl + 1);
            } else {
                yoff  += hbs * 8 * bytesperpixel;
                uvoff += hbs * 8 * bytesperpixel >> s->ss_h;
                decode_sb_mem(td, row, col + hbs, lflvl, yoff, uvoff, bl + 1);
            }
        } else if (row + hbs < s->rows) {
            yoff  += hbs * 8 * y_stride;
            uvoff += hbs * 8 * uv_stride >> s->ss_v;
            decode_sb_mem(td, row + hbs, col, lflvl, yoff, uvoff, bl + 1);
        }
    }
}