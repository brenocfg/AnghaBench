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
 int HEVC_NAL_AUD ; 
 int HEVC_NAL_PPS ; 
 int HEVC_NAL_SEI_PREFIX ; 
 int HEVC_NAL_SPS ; 
 int HEVC_NAL_VPS ; 
 int START_CODE ; 
 scalar_t__* avpriv_find_start_code (scalar_t__ const*,scalar_t__ const*,int*) ; 

__attribute__((used)) static int hevc_split(AVCodecContext *avctx, const uint8_t *buf, int buf_size)
{
    const uint8_t *ptr = buf, *end = buf + buf_size;
    uint32_t state = -1;
    int has_vps = 0;
    int has_sps = 0;
    int has_pps = 0;
    int nut;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &state);
        if ((state >> 8) != START_CODE)
            break;
        nut = (state >> 1) & 0x3F;
        if (nut == HEVC_NAL_VPS)
            has_vps = 1;
        else if (nut == HEVC_NAL_SPS)
            has_sps = 1;
        else if (nut == HEVC_NAL_PPS)
            has_pps = 1;
        else if ((nut != HEVC_NAL_SEI_PREFIX || has_pps) &&
                  nut != HEVC_NAL_AUD) {
            if (has_vps && has_sps) {
                while (ptr - 4 > buf && ptr[-5] == 0)
                    ptr--;
                return ptr - 4 - buf;
            }
        }
    }
    return 0;
}