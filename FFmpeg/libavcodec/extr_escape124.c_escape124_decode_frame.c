#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_22__ {int /*<<< orphan*/  blocks; } ;
struct TYPE_21__ {int width; TYPE_2__* priv_data; } ;
struct TYPE_20__ {int* linesize; scalar_t__* data; } ;
struct TYPE_19__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {long long num_superblocks; TYPE_4__* frame; TYPE_6__* codebooks; } ;
struct TYPE_17__ {int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_1__ SuperBlock ;
typedef  int /*<<< orphan*/  MacroBlock ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ Escape124Context ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int INT_MAX ; 
 int av_frame_ref (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_log2 (unsigned int) ; 
 int /*<<< orphan*/  copy_superblock (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_macroblock (TYPE_2__*,int /*<<< orphan*/ *,unsigned int*,unsigned int) ; 
 unsigned int decode_skip_count (int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  insert_mb_into_sb (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* mask_matrix ; 
 TYPE_6__ unpack_codebook (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int escape124_decode_frame(AVCodecContext *avctx,
                                  void *data, int *got_frame,
                                  AVPacket *avpkt)
{
    int buf_size = avpkt->size;
    Escape124Context *s = avctx->priv_data;
    AVFrame *frame = data;

    GetBitContext gb;
    unsigned frame_flags, frame_size;
    unsigned i;

    unsigned superblock_index, cb_index = 1,
             superblock_col_index = 0,
             superblocks_per_row = avctx->width / 8, skip = -1;

    uint16_t* old_frame_data, *new_frame_data;
    unsigned old_stride, new_stride;

    int ret;

    if ((ret = init_get_bits8(&gb, avpkt->data, avpkt->size)) < 0)
        return ret;

    // This call also guards the potential depth reads for the
    // codebook unpacking.
    // Check if the amount we will read minimally is available on input.
    // The 64 represent the immediately next 2 frame_* elements read, the 23/4320
    // represent a lower bound of the space needed for skipped superblocks. Non
    // skipped SBs need more space.
    if (get_bits_left(&gb) < 64 + s->num_superblocks * 23LL / 4320)
        return -1;

    frame_flags = get_bits_long(&gb, 32);
    frame_size  = get_bits_long(&gb, 32);

    // Leave last frame unchanged
    // FIXME: Is this necessary?  I haven't seen it in any real samples
    if (!(frame_flags & 0x114) || !(frame_flags & 0x7800000)) {
        if (!s->frame->data[0])
            return AVERROR_INVALIDDATA;

        av_log(avctx, AV_LOG_DEBUG, "Skipping frame\n");

        *got_frame = 1;
        if ((ret = av_frame_ref(frame, s->frame)) < 0)
            return ret;

        return frame_size;
    }

    for (i = 0; i < 3; i++) {
        if (frame_flags & (1 << (17 + i))) {
            unsigned cb_depth, cb_size;
            if (i == 2) {
                // This codebook can be cut off at places other than
                // powers of 2, leaving some of the entries undefined.
                cb_size = get_bits_long(&gb, 20);
                if (!cb_size) {
                    av_log(avctx, AV_LOG_ERROR, "Invalid codebook size 0.\n");
                    return AVERROR_INVALIDDATA;
                }
                cb_depth = av_log2(cb_size - 1) + 1;
            } else {
                cb_depth = get_bits(&gb, 4);
                if (i == 0) {
                    // This is the most basic codebook: pow(2,depth) entries
                    // for a depth-length key
                    cb_size = 1 << cb_depth;
                } else {
                    // This codebook varies per superblock
                    // FIXME: I don't think this handles integer overflow
                    // properly
                    cb_size = s->num_superblocks << cb_depth;
                }
            }
            if (s->num_superblocks >= INT_MAX >> cb_depth) {
                av_log(avctx, AV_LOG_ERROR, "Depth or num_superblocks are too large\n");
                return AVERROR_INVALIDDATA;
            }

            av_freep(&s->codebooks[i].blocks);
            s->codebooks[i] = unpack_codebook(&gb, cb_depth, cb_size);
            if (!s->codebooks[i].blocks)
                return -1;
        }
    }

    if ((ret = ff_get_buffer(avctx, frame, AV_GET_BUFFER_FLAG_REF)) < 0)
        return ret;

    new_frame_data = (uint16_t*)frame->data[0];
    new_stride = frame->linesize[0] / 2;
    old_frame_data = (uint16_t*)s->frame->data[0];
    old_stride = s->frame->linesize[0] / 2;

    for (superblock_index = 0; superblock_index < s->num_superblocks;
         superblock_index++) {
        MacroBlock mb;
        SuperBlock sb;
        unsigned multi_mask = 0;

        if (skip == -1) {
            // Note that this call will make us skip the rest of the blocks
            // if the frame prematurely ends
            skip = decode_skip_count(&gb);
        }

        if (skip) {
            copy_superblock(new_frame_data, new_stride,
                            old_frame_data, old_stride);
        } else {
            copy_superblock(sb.pixels, 8,
                            old_frame_data, old_stride);

            while (get_bits_left(&gb) >= 1 && !get_bits1(&gb)) {
                unsigned mask;
                mb = decode_macroblock(s, &gb, &cb_index, superblock_index);
                mask = get_bits(&gb, 16);
                multi_mask |= mask;
                for (i = 0; i < 16; i++) {
                    if (mask & mask_matrix[i]) {
                        insert_mb_into_sb(&sb, mb, i);
                    }
                }
            }

            if (!get_bits1(&gb)) {
                unsigned inv_mask = get_bits(&gb, 4);
                for (i = 0; i < 4; i++) {
                    if (inv_mask & (1 << i)) {
                        multi_mask ^= 0xF << i*4;
                    } else {
                        multi_mask ^= get_bits(&gb, 4) << i*4;
                    }
                }

                for (i = 0; i < 16; i++) {
                    if (multi_mask & mask_matrix[i]) {
                        mb = decode_macroblock(s, &gb, &cb_index,
                                               superblock_index);
                        insert_mb_into_sb(&sb, mb, i);
                    }
                }
            } else if (frame_flags & (1 << 16)) {
                while (get_bits_left(&gb) >= 1 && !get_bits1(&gb)) {
                    mb = decode_macroblock(s, &gb, &cb_index, superblock_index);
                    insert_mb_into_sb(&sb, mb, get_bits(&gb, 4));
                }
            }

            copy_superblock(new_frame_data, new_stride, sb.pixels, 8);
        }

        superblock_col_index++;
        new_frame_data += 8;
        if (old_frame_data)
            old_frame_data += 8;
        if (superblock_col_index == superblocks_per_row) {
            new_frame_data += new_stride * 8 - superblocks_per_row * 8;
            if (old_frame_data)
                old_frame_data += old_stride * 8 - superblocks_per_row * 8;
            superblock_col_index = 0;
        }
        skip--;
    }

    av_log(avctx, AV_LOG_DEBUG,
           "Escape sizes: %i, %i, %i\n",
           frame_size, buf_size, get_bits_count(&gb) / 8);

    av_frame_unref(s->frame);
    if ((ret = av_frame_ref(s->frame, frame)) < 0)
        return ret;

    *got_frame = 1;

    return frame_size;
}