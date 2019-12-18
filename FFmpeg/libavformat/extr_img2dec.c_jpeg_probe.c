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
struct TYPE_3__ {int* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
#define  APP0 155 
#define  APP1 154 
#define  APP10 153 
#define  APP11 152 
#define  APP12 151 
#define  APP13 150 
#define  APP14 149 
#define  APP15 148 
#define  APP2 147 
#define  APP3 146 
#define  APP4 145 
#define  APP5 144 
#define  APP6 143 
#define  APP7 142 
#define  APP8 141 
#define  APP9 140 
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB16 (int const*) ; 
 int AV_RB32 (int const*) ; 
#define  COM 139 
#define  DQT 138 
#define  EOI 137 
 int JPG ; 
#define  SOF0 136 
#define  SOF1 135 
#define  SOF2 134 
#define  SOF3 133 
#define  SOF5 132 
#define  SOF6 131 
#define  SOF7 130 
#define  SOI 129 
#define  SOS 128 
 int TEM ; 

__attribute__((used)) static int jpeg_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;
    int i, state = SOI;

    if (AV_RB16(b) != 0xFFD8 ||
        AV_RB32(b) == 0xFFD8FFF7)
    return 0;

    b += 2;
    for (i = 0; i < p->buf_size - 3; i++) {
        int c;
        if (b[i] != 0xFF)
            continue;
        c = b[i + 1];
        switch (c) {
        case SOI:
            return 0;
        case SOF0:
        case SOF1:
        case SOF2:
        case SOF3:
        case SOF5:
        case SOF6:
        case SOF7:
            i += AV_RB16(&b[i + 2]) + 1;
            if (state != SOI)
                return 0;
            state = SOF0;
            break;
        case SOS:
            i += AV_RB16(&b[i + 2]) + 1;
            if (state != SOF0 && state != SOS)
                return 0;
            state = SOS;
            break;
        case EOI:
            if (state != SOS)
                return 0;
            state = EOI;
            break;
        case DQT:
        case APP0:
        case APP1:
        case APP2:
        case APP3:
        case APP4:
        case APP5:
        case APP6:
        case APP7:
        case APP8:
        case APP9:
        case APP10:
        case APP11:
        case APP12:
        case APP13:
        case APP14:
        case APP15:
        case COM:
            i += AV_RB16(&b[i + 2]) + 1;
            break;
        default:
            if (  (c > TEM && c < SOF0)
                || c == JPG)
                return 0;
        }
    }

    if (state == EOI)
        return AVPROBE_SCORE_EXTENSION + 1;
    if (state == SOS)
        return AVPROBE_SCORE_EXTENSION / 2;
    return AVPROBE_SCORE_EXTENSION / 8;
}