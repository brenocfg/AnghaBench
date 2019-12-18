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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {float re; } ;
typedef  TYPE_1__ FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uintp2_c (float,int) ; 

__attribute__((used)) static void export_row16(FFTComplex *src, uint8_t *dstp, int rw, float scale, int depth)
{
    uint16_t *dst = (uint16_t *)dstp;
    int j;

    for (j = 0; j < rw; j++)
        dst[j] = av_clip_uintp2_c(src[j].re * scale + 0.5f, depth);
}