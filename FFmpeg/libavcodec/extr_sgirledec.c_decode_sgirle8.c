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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int FFMIN (int,int) ; 
 int FFMIN3 (int,int,int) ; 
 int /*<<< orphan*/  INC_XY (int) ; 
 int /*<<< orphan*/  RBG323_TO_BGR8 (int const) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rbg323_to_bgr8 (int*,int const*,int) ; 

__attribute__((used)) static int decode_sgirle8(AVCodecContext *avctx, uint8_t *dst,
                          const uint8_t *src, int src_size,
                          int width, int height, ptrdiff_t linesize)
{
    const uint8_t *src_end = src + src_size;
    int x = 0, y = 0;

#define INC_XY(n)                                                             \
    x += n;                                                                   \
    if (x >= width) {                                                         \
        y++;                                                                  \
        if (y >= height)                                                      \
            return 0;                                                         \
        x = 0;                                                                \
    }

    while (src_end - src >= 2) {
        uint8_t v = *src++;
        if (v > 0 && v < 0xC0) {
            do {
                int length = FFMIN(v, width - x);
                if (length <= 0)
                    break;
                memset(dst + y * linesize + x, RBG323_TO_BGR8(*src), length);
                INC_XY(length);
                v -= length;
            } while (v > 0);
            src++;
        } else if (v >= 0xC1) {
            v -= 0xC0;
            do {
                int length = FFMIN3(v, width - x, src_end - src);
                if (src_end - src < length || length <= 0)
                    break;
                rbg323_to_bgr8(dst + y * linesize + x, src, length);
                INC_XY(length);
                src += length;
                v   -= length;
            } while (v > 0);
        } else {
            avpriv_request_sample(avctx, "opcode %d", v);
            return AVERROR_PATCHWELCOME;
        }
    }
    return 0;
}