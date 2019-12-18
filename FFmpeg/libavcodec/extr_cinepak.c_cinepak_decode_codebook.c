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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int8_t ;
typedef  int* cvid_codebook ;

/* Variables and functions */
 int AV_RB32 (int const*) ; 
 void* av_clip_uint8 (int) ; 

__attribute__((used)) static void cinepak_decode_codebook (cvid_codebook *codebook,
                                     int chunk_id, int size, const uint8_t *data)
{
    const uint8_t *eod = (data + size);
    uint32_t flag, mask;
    int      i, n;
    uint8_t *p;

    /* check if this chunk contains 4- or 6-element vectors */
    n    = (chunk_id & 0x04) ? 4 : 6;
    flag = 0;
    mask = 0;

    p = codebook[0];
    for (i=0; i < 256; i++) {
        if ((chunk_id & 0x01) && !(mask >>= 1)) {
            if ((data + 4) > eod)
                break;

            flag  = AV_RB32 (data);
            data += 4;
            mask  = 0x80000000;
        }

        if (!(chunk_id & 0x01) || (flag & mask)) {
            int k, kk;

            if ((data + n) > eod)
                break;

            for (k = 0; k < 4; ++k) {
                int r = *data++;
                for (kk = 0; kk < 3; ++kk)
                    *p++ = r;
            }
            if (n == 6) {
                int r, g, b, u, v;
                u = *(int8_t *)data++;
                v = *(int8_t *)data++;
                p -= 12;
                for(k=0; k<4; ++k) {
                    r = *p++ + v*2;
                    g = *p++ - (u/2) - v;
                    b = *p   + u*2;
                    p -= 2;
                    *p++ = av_clip_uint8(r);
                    *p++ = av_clip_uint8(g);
                    *p++ = av_clip_uint8(b);
                }
            }
        } else {
            p += 12;
        }
    }
}