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
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  ulti_convert_yuv (int /*<<< orphan*/ *,int,int,int*,int) ; 

__attribute__((used)) static void ulti_pattern(AVFrame *frame, int x, int y,
                         int f0, int f1, int Y0, int Y1, int chroma)
{
    uint8_t Luma[16];
    int mask, i;
    for(mask = 0x80, i = 0; mask; mask >>= 1, i++) {
        if(f0 & mask)
            Luma[i] = Y1;
        else
            Luma[i] = Y0;
    }

    for(mask = 0x80, i = 8; mask; mask >>= 1, i++) {
        if(f1 & mask)
            Luma[i] = Y1;
        else
            Luma[i] = Y0;
    }

    ulti_convert_yuv(frame, x, y, Luma, chroma);
}