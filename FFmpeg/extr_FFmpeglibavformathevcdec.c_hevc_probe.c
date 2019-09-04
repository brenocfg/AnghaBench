#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
#define  HEVC_NAL_BLA_N_LP 136 
#define  HEVC_NAL_BLA_W_LP 135 
#define  HEVC_NAL_BLA_W_RADL 134 
#define  HEVC_NAL_CRA_NUT 133 
#define  HEVC_NAL_IDR_N_LP 132 
#define  HEVC_NAL_IDR_W_RADL 131 
#define  HEVC_NAL_PPS 130 
#define  HEVC_NAL_SPS 129 
#define  HEVC_NAL_VPS 128 

__attribute__((used)) static int hevc_probe(const AVProbeData *p)
{
    uint32_t code = -1;
    int vps = 0, sps = 0, pps = 0, irap = 0;
    int i;

    for (i = 0; i < p->buf_size - 1; i++) {
        code = (code << 8) + p->buf[i];
        if ((code & 0xffffff00) == 0x100) {
            uint8_t nal2 = p->buf[i + 1];
            int type = (code & 0x7E) >> 1;

            if (code & 0x81) // forbidden and reserved zero bits
                return 0;

            if (nal2 & 0xf8) // reserved zero
                return 0;

            switch (type) {
            case HEVC_NAL_VPS:        vps++;  break;
            case HEVC_NAL_SPS:        sps++;  break;
            case HEVC_NAL_PPS:        pps++;  break;
            case HEVC_NAL_BLA_N_LP:
            case HEVC_NAL_BLA_W_LP:
            case HEVC_NAL_BLA_W_RADL:
            case HEVC_NAL_CRA_NUT:
            case HEVC_NAL_IDR_N_LP:
            case HEVC_NAL_IDR_W_RADL: irap++; break;
            }
        }
    }

    if (vps && sps && pps && irap)
        return AVPROBE_SCORE_EXTENSION + 1; // 1 more than .mpg
    return 0;
}