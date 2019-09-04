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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum FilterMode { ____Placeholder_FilterMode } FilterMode ;

/* Variables and functions */
#define  MODE_DEINTERLEAVE 130 
#define  MODE_INTERLEAVE 129 
#define  MODE_NONE 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void interleave(uint8_t *dst, uint8_t *src, int w, int h,
                       int dst_linesize, int src_linesize,
                       enum FilterMode mode, int swap)
{
    const int a = swap;
    const int b = 1 - a;
    const int m = h >> 1;
    int y;

    switch (mode) {
    case MODE_DEINTERLEAVE:
        for (y = 0; y < m; y++) {
            memcpy(dst + dst_linesize *  y     , src + src_linesize * (y * 2 + a), w);
            memcpy(dst + dst_linesize * (y + m), src + src_linesize * (y * 2 + b), w);
        }
        break;
    case MODE_NONE:
        for (y = 0; y < m; y++) {
            memcpy(dst + dst_linesize *  y * 2     , src + src_linesize * (y * 2 + a), w);
            memcpy(dst + dst_linesize * (y * 2 + 1), src + src_linesize * (y * 2 + b), w);
        }
        break;
    case MODE_INTERLEAVE:
        for (y = 0; y < m; y++) {
            memcpy(dst + dst_linesize * (y * 2 + a), src + src_linesize *  y     , w);
            memcpy(dst + dst_linesize * (y * 2 + b), src + src_linesize * (y + m), w);
        }
        break;
    }
}