#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
struct TYPE_11__ {int width; int height; scalar_t__ mv_ptr; scalar_t__ tree; scalar_t__ ypos; scalar_t__ xpos; } ;
struct TYPE_10__ {unsigned int num_vectors; int /*<<< orphan*/  const* last_byte; scalar_t__ need_resync; scalar_t__ skip_bits; int /*<<< orphan*/  gb; int /*<<< orphan*/  const* mc_vectors; int /*<<< orphan*/  avctx; } ;
struct TYPE_9__ {int width; int height; } ;
typedef  TYPE_1__ Plane ;
typedef  TYPE_2__ Indeo3DecodeContext ;
typedef  TYPE_3__ Cell ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CELL_STACK_MAX ; 
 int /*<<< orphan*/  INTRA_NULL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int bytestream_get_le32 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int parse_bintree (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_plane(Indeo3DecodeContext *ctx, AVCodecContext *avctx,
                        Plane *plane, const uint8_t *data, int32_t data_size,
                        int32_t strip_width)
{
    Cell            curr_cell;
    unsigned        num_vectors;

    /* each plane data starts with mc_vector_count field, */
    /* an optional array of motion vectors followed by the vq data */
    num_vectors = bytestream_get_le32(&data); data_size -= 4;
    if (num_vectors > 256) {
        av_log(ctx->avctx, AV_LOG_ERROR,
               "Read invalid number of motion vectors %d\n", num_vectors);
        return AVERROR_INVALIDDATA;
    }
    if (num_vectors * 2 > data_size)
        return AVERROR_INVALIDDATA;

    ctx->num_vectors = num_vectors;
    ctx->mc_vectors  = num_vectors ? data : 0;

    /* init the bitreader */
    init_get_bits(&ctx->gb, &data[num_vectors * 2], (data_size - num_vectors * 2) << 3);
    ctx->skip_bits   = 0;
    ctx->need_resync = 0;

    ctx->last_byte = data + data_size;

    /* initialize the 1st cell and set its dimensions to whole plane */
    curr_cell.xpos   = curr_cell.ypos = 0;
    curr_cell.width  = plane->width  >> 2;
    curr_cell.height = plane->height >> 2;
    curr_cell.tree   = 0; // we are in the MC tree now
    curr_cell.mv_ptr = 0; // no motion vector = INTRA cell

    return parse_bintree(ctx, avctx, plane, INTRA_NULL, &curr_cell, CELL_STACK_MAX, strip_width);
}