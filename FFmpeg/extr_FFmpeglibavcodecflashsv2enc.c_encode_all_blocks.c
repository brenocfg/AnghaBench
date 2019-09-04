#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ len; scalar_t__ height; scalar_t__ enc_size; scalar_t__ data_size; scalar_t__ dirty; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int rows; int cols; int image_width; int block_height; int block_width; int raw_size; int image_height; int tot_blocks; int /*<<< orphan*/  uncomp_size; int /*<<< orphan*/  comp_size; int /*<<< orphan*/  diff_blocks; int /*<<< orphan*/  dist; int /*<<< orphan*/  comp; int /*<<< orphan*/  palette; int /*<<< orphan*/ * current_frame; scalar_t__ use15_7; TYPE_2__* key_blocks; TYPE_2__* frame_blocks; } ;
typedef  TYPE_1__ FlashSV2Context ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 int /*<<< orphan*/  COLORSPACE_15_7 ; 
 int /*<<< orphan*/  HAS_DIFF_BLOCKS ; 
 int encode_block (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int encode_all_blocks(FlashSV2Context * s, int keyframe)
{
    int row, col, res;
    uint8_t *data;
    Block *b, *prev;
    for (row = 0; row < s->rows; row++) {
        for (col = 0; col < s->cols; col++) {
            b = s->frame_blocks + (row * s->cols + col);
            prev = s->key_blocks + (row * s->cols + col);
            b->flags = s->use15_7 ? COLORSPACE_15_7 : 0;
            if (keyframe) {
                b->start = 0;
                b->len = b->height;
            } else if (!b->dirty) {
                b->start = 0;
                b->len = 0;
                b->data_size = 0;
                continue;
            } else if (b->start != 0 || b->len != b->height) {
                b->flags |= HAS_DIFF_BLOCKS;
            }
            data = s->current_frame + s->image_width * 3 * s->block_height * row + s->block_width * col * 3;
            res = encode_block(s, &s->palette, b, prev, data, s->image_width * 3, s->comp, s->dist, keyframe);
#ifndef FLASHSV2_DUMB
            if (b->dirty)
                s->diff_blocks++;
            s->comp_size += b->data_size;
            s->uncomp_size += b->enc_size;
#endif
            if (res)
                return res;
        }
    }
#ifndef FLASHSV2_DUMB
    s->raw_size += s->image_width * s->image_height * 3;
    s->tot_blocks += s->rows * s->cols;
#endif
    return 0;
}