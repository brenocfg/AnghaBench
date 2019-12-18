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
 int /*<<< orphan*/  PUTBITS4 (int) ; 

__attribute__((used)) static void dvb_encode_rle4(uint8_t **pq,
                            const uint8_t *bitmap, int linesize,
                            int w, int h)
{
    uint8_t *q;
    unsigned int bitbuf;
    int bitcnt;
    int x, y, len, x1, v, color;

    q = *pq;

    for(y = 0; y < h; y++) {
        *q++ = 0x11;
        bitbuf = 0;
        bitcnt = 4;

        x = 0;
        while (x < w) {
            x1 = x;
            color = bitmap[x1++];
            while (x1 < w && bitmap[x1] == color)
                x1++;
            len = x1 - x;
            if (color == 0 && len == 2) {
                PUTBITS4(0);
                PUTBITS4(0xd);
            } else if (color == 0 && (len >= 3 && len <= 9)) {
                PUTBITS4(0);
                PUTBITS4(len - 2);
            } else if (len >= 4 && len <= 7) {
                PUTBITS4(0);
                PUTBITS4(8 + len - 4);
                PUTBITS4(color);
            } else if (len >= 9 && len <= 24) {
                PUTBITS4(0);
                PUTBITS4(0xe);
                PUTBITS4(len - 9);
                PUTBITS4(color);
            } else if (len >= 25) {
                if (len > 280)
                    len = 280;
                v = len - 25;
                PUTBITS4(0);
                PUTBITS4(0xf);
                PUTBITS4(v >> 4);
                PUTBITS4(v & 0xf);
                PUTBITS4(color);
            } else {
                PUTBITS4(color);
                if (color == 0) {
                    PUTBITS4(0xc);
                }
                len = 1;
            }
            x += len;
        }
        /* end of line */
        PUTBITS4(0);
        PUTBITS4(0);
        if (bitcnt != 4) {
            *q++ = bitbuf;
        }
        *q++ = 0xf0;
        bitmap += linesize;
    }
    *pq = q;
}