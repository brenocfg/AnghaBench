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

/* Variables and functions */
 int FFMIN (int,int) ; 

__attribute__((used)) static void dvb_encode_rle8(uint8_t **pq,
                            const uint8_t *bitmap, int linesize,
                            int w, int h)
{
    uint8_t *q;
    int x, y, len, x1, color;

    q = *pq;

    for (y = 0; y < h; y++) {
        *q++ = 0x12;

        x = 0;
        while (x < w) {
            x1 = x;
            color = bitmap[x1++];
            while (x1 < w && bitmap[x1] == color)
                x1++;
            len = x1 - x;
            if (len == 1 && color) {
                // 00000001 to 11111111           1 pixel in colour x
                *q++ = color;
            } else {
                if (color == 0x00) {
                    // 00000000 0LLLLLLL          L pixels (1-127) in colour 0 (L > 0)
                    len = FFMIN(len, 127);
                    *q++ = 0x00;
                    *q++ = len;
                } else if (len > 2) {
                    // 00000000 1LLLLLLL CCCCCCCC L pixels (3-127) in colour C (L > 2)
                    len = FFMIN(len, 127);
                    *q++ = 0x00;
                    *q++ = 0x80+len;
                    *q++ = color;
                }
                else if (len == 2) {
                    *q++ = color;
                    *q++ = color;
                } else {
                    *q++ = color;
                    len = 1;
                }
            }
            x += len;
        }
        /* end of line */
        // 00000000 end of 8-bit/pixel_code_string
        *q++ = 0x00;
        *q++ = 0xf0;
        bitmap += linesize;
    }
    *pq = q;
}