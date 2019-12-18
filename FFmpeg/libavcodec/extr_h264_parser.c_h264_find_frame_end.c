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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ (* startcode_find_candidate ) (int const*,int) ;} ;
struct TYPE_6__ {int state; int frame_start_found; } ;
struct TYPE_7__ {int nal_length_size; unsigned int parse_last_mb; int* parse_history; int parse_history_count; scalar_t__ is_avc; TYPE_1__ h264dsp; TYPE_2__ pc; } ;
typedef  TYPE_2__ ParseContext ;
typedef  TYPE_3__ H264ParseContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int END_NOT_FOUND ; 
 int H264_NAL_AUD ; 
 int H264_NAL_DPA ; 
 int H264_NAL_IDR_SLICE ; 
 int H264_NAL_PPS ; 
 int H264_NAL_SEI ; 
 int H264_NAL_SLICE ; 
 int H264_NAL_SPS ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ stub1 (int const*,int) ; 

__attribute__((used)) static int h264_find_frame_end(H264ParseContext *p, const uint8_t *buf,
                               int buf_size, void *logctx)
{
    int i, j;
    uint32_t state;
    ParseContext *pc = &p->pc;

    int next_avc = p->is_avc ? 0 : buf_size;
//    mb_addr= pc->mb_addr - 1;
    state = pc->state;
    if (state > 13)
        state = 7;

    if (p->is_avc && !p->nal_length_size)
        av_log(logctx, AV_LOG_ERROR, "AVC-parser: nal length size invalid\n");

    for (i = 0; i < buf_size; i++) {
        if (i >= next_avc) {
            int nalsize = 0;
            i = next_avc;
            for (j = 0; j < p->nal_length_size; j++)
                nalsize = (nalsize << 8) | buf[i++];
            if (nalsize <= 0 || nalsize > buf_size - i) {
                av_log(logctx, AV_LOG_ERROR, "AVC-parser: nal size %d remaining %d\n", nalsize, buf_size - i);
                return buf_size;
            }
            next_avc = i + nalsize;
            state    = 5;
        }

        if (state == 7) {
            i += p->h264dsp.startcode_find_candidate(buf + i, next_avc - i);
            if (i < next_avc)
                state = 2;
        } else if (state <= 2) {
            if (buf[i] == 1)
                state ^= 5;            // 2->7, 1->4, 0->5
            else if (buf[i])
                state = 7;
            else
                state >>= 1;           // 2->1, 1->0, 0->0
        } else if (state <= 5) {
            int nalu_type = buf[i] & 0x1F;
            if (nalu_type == H264_NAL_SEI || nalu_type == H264_NAL_SPS ||
                nalu_type == H264_NAL_PPS || nalu_type == H264_NAL_AUD) {
                if (pc->frame_start_found) {
                    i++;
                    goto found;
                }
            } else if (nalu_type == H264_NAL_SLICE || nalu_type == H264_NAL_DPA ||
                       nalu_type == H264_NAL_IDR_SLICE) {
                state += 8;
                continue;
            }
            state = 7;
        } else {
            unsigned int mb, last_mb = p->parse_last_mb;
            GetBitContext gb;
            p->parse_history[p->parse_history_count++] = buf[i];

            init_get_bits(&gb, p->parse_history, 8*p->parse_history_count);
            mb= get_ue_golomb_long(&gb);
            if (get_bits_left(&gb) > 0 || p->parse_history_count > 5) {
                p->parse_last_mb = mb;
                if (pc->frame_start_found) {
                    if (mb <= last_mb) {
                        i -= p->parse_history_count - 1;
                        p->parse_history_count = 0;
                        goto found;
                    }
                } else
                    pc->frame_start_found = 1;
                p->parse_history_count = 0;
                state = 7;
            }
        }
    }
    pc->state = state;
    if (p->is_avc)
        return next_avc;
    return END_NOT_FOUND;

found:
    pc->state             = 7;
    pc->frame_start_found = 0;
    if (p->is_avc)
        return next_avc;
    return i - (state & 5);
}