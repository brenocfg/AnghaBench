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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_int16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dss_sp_32to16bit(int16_t *dst, int32_t *src, int size)
{
    int i;

    for (i = 0; i < size; i++)
        dst[i] = av_clip_int16(src[i]);
}