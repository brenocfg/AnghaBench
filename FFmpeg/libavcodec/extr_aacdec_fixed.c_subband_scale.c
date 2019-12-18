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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int* exp2tab ; 

__attribute__((used)) static void subband_scale(int *dst, int *src, int scale, int offset, int len, void *log_context)
{
    int ssign = scale < 0 ? -1 : 1;
    int s = FFABS(scale);
    unsigned int round;
    int i, out, c = exp2tab[s & 3];

    s = offset - (s >> 2);

    if (s > 31) {
        for (i=0; i<len; i++) {
            dst[i] = 0;
        }
    } else if (s > 0) {
        round = 1 << (s-1);
        for (i=0; i<len; i++) {
            out = (int)(((int64_t)src[i] * c) >> 32);
            dst[i] = ((int)(out+round) >> s) * ssign;
        }
    } else if (s > -32) {
        s = s + 32;
        round = 1U << (s-1);
        for (i=0; i<len; i++) {
            out = (int)((int64_t)((int64_t)src[i] * c + round) >> s);
            dst[i] = out * (unsigned)ssign;
        }
    } else {
        av_log(log_context, AV_LOG_ERROR, "Overflow in subband_scale()\n");
    }
}