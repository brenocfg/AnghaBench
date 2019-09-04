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

/* Variables and functions */
 int /*<<< orphan*/  decompose2D (float*,float*,float*,int,int,int,int,int) ; 

__attribute__((used)) static void decompose2D2(float *dst[4], float *src, float *temp[2],
                         int linesize, int step, int w, int h)
{
    decompose2D(temp[0], temp[1], src,     1, linesize, step, w, h);
    decompose2D( dst[0],  dst[1], temp[0], linesize, 1, step, h, w);
    decompose2D( dst[2],  dst[3], temp[1], linesize, 1, step, h, w);
}