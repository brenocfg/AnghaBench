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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int checkline(void *ctx, const unsigned char *src, int stride, int len, int bpp)
{
    int total = 0;
    int div = len;
    const uint16_t *src16 = (const uint16_t *)src;

    switch (bpp) {
    case 1:
        while (len >= 8) {
            total += src[       0] + src[  stride] + src[2*stride] + src[3*stride]
                  +  src[4*stride] + src[5*stride] + src[6*stride] + src[7*stride];
            src += 8*stride;
            len -= 8;
        }
        while (--len >= 0) {
            total += src[0];
            src += stride;
        }
        break;
    case 2:
        stride >>= 1;
        while (len >= 8) {
            total += src16[       0] + src16[  stride] + src16[2*stride] + src16[3*stride]
                  +  src16[4*stride] + src16[5*stride] + src16[6*stride] + src16[7*stride];
            src16 += 8*stride;
            len -= 8;
        }
        while (--len >= 0) {
            total += src16[0];
            src16 += stride;
        }
        break;
    case 3:
    case 4:
        while (len >= 4) {
            total += src[0]        + src[1         ] + src[2         ]
                  +  src[  stride] + src[1+  stride] + src[2+  stride]
                  +  src[2*stride] + src[1+2*stride] + src[2+2*stride]
                  +  src[3*stride] + src[1+3*stride] + src[2+3*stride];
            src += 4*stride;
            len -= 4;
        }
        while (--len >= 0) {
            total += src[0] + src[1] + src[2];
            src += stride;
        }
        div *= 3;
        break;
    }
    total /= div;

    av_log(ctx, AV_LOG_DEBUG, "total:%d\n", total);
    return total;
}