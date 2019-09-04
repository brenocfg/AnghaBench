#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int H264_NAL_AUD ; 
 int H264_NAL_PPS ; 
 int H264_NAL_SEI ; 
 int H264_NAL_SPS ; 
 int H264_NAL_SPS_EXT ; 
 scalar_t__* avpriv_find_start_code (scalar_t__ const*,scalar_t__ const*,int*) ; 

__attribute__((used)) static int h264_split(AVCodecContext *avctx,
                      const uint8_t *buf, int buf_size)
{
    uint32_t state = -1;
    int has_sps    = 0;
    int has_pps    = 0;
    const uint8_t *ptr = buf, *end = buf + buf_size;
    int nalu_type;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &state);
        if ((state & 0xFFFFFF00) != 0x100)
            break;
        nalu_type = state & 0x1F;
        if (nalu_type == H264_NAL_SPS) {
            has_sps = 1;
        } else if (nalu_type == H264_NAL_PPS)
            has_pps = 1;
        /* else if (nalu_type == 0x01 ||
         *     nalu_type == 0x02 ||
         *     nalu_type == 0x05) {
         *  }
         */
        else if ((nalu_type != H264_NAL_SEI || has_pps) &&
                  nalu_type != H264_NAL_AUD && nalu_type != H264_NAL_SPS_EXT &&
                  nalu_type != 0x0f) {
            if (has_sps) {
                while (ptr - 4 > buf && ptr[-5] == 0)
                    ptr--;
                return ptr - 4 - buf;
            }
        }
    }

    return 0;
}