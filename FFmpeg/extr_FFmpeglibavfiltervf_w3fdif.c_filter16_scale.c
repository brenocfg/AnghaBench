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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int av_clip (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void filter16_scale(uint8_t *out_pixel8, const int32_t *work_pixel, int linesize, int max)
{
    uint16_t *out_pixel = (uint16_t *)out_pixel8;
    int j;

    linesize /= 2;
    for (j = 0; j < linesize; j++, out_pixel++, work_pixel++)
        *out_pixel = av_clip(*work_pixel, 0, max) >> 15;
}