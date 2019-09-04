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
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {int state64; int frame_start_found; } ;
struct TYPE_6__ {TYPE_1__ pc; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ HEVCParserContext ;
typedef  TYPE_3__ AVCodecParserContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 int HEVC_NAL_BLA_W_LP ; 
 int HEVC_NAL_CRA_NUT ; 
 int HEVC_NAL_EOB_NUT ; 
 int HEVC_NAL_RASL_R ; 
 int HEVC_NAL_SEI_PREFIX ; 
 int HEVC_NAL_VPS ; 
 int START_CODE ; 

__attribute__((used)) static int hevc_find_frame_end(AVCodecParserContext *s, const uint8_t *buf,
                               int buf_size)
{
    HEVCParserContext *ctx = s->priv_data;
    ParseContext       *pc = &ctx->pc;
    int i;

    for (i = 0; i < buf_size; i++) {
        int nut;

        pc->state64 = (pc->state64 << 8) | buf[i];

        if (((pc->state64 >> 3 * 8) & 0xFFFFFF) != START_CODE)
            continue;

        nut = (pc->state64 >> 2 * 8 + 1) & 0x3F;
        // Beginning of access unit
        if ((nut >= HEVC_NAL_VPS && nut <= HEVC_NAL_EOB_NUT) || nut == HEVC_NAL_SEI_PREFIX ||
            (nut >= 41 && nut <= 44) || (nut >= 48 && nut <= 55)) {
            if (pc->frame_start_found) {
                pc->frame_start_found = 0;
                return i - 5;
            }
        } else if (nut <= HEVC_NAL_RASL_R ||
                   (nut >= HEVC_NAL_BLA_W_LP && nut <= HEVC_NAL_CRA_NUT)) {
            int first_slice_segment_in_pic_flag = buf[i] >> 7;
            if (first_slice_segment_in_pic_flag) {
                if (!pc->frame_start_found) {
                    pc->frame_start_found = 1;
                } else { // First slice of next frame found
                    pc->frame_start_found = 0;
                    return i - 5;
                }
            }
        }
    }

    return END_NOT_FOUND;
}