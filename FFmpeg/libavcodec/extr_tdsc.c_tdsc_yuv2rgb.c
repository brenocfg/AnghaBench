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

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int) ; 

__attribute__((used)) static inline void tdsc_yuv2rgb(uint8_t *out, int Y, int U, int V)
{
    out[0] = av_clip_uint8(Y + (             91881 * V + 32768 >> 16));
    out[1] = av_clip_uint8(Y + (-22554 * U - 46802 * V + 32768 >> 16));
    out[2] = av_clip_uint8(Y + (116130 * U             + 32768 >> 16));
}