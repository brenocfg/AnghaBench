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
typedef  int /*<<< orphan*/ ** Mtx ;

/* Variables and functions */

void c_guMtxCopy(Mtx src,Mtx dst)
{
	if(src==dst) return;

    dst[0][0] = src[0][0];    dst[0][1] = src[0][1];    dst[0][2] = src[0][2];    dst[0][3] = src[0][3];
    dst[1][0] = src[1][0];    dst[1][1] = src[1][1];    dst[1][2] = src[1][2];    dst[1][3] = src[1][3];
    dst[2][0] = src[2][0];    dst[2][1] = src[2][1];    dst[2][2] = src[2][2];    dst[2][3] = src[2][3];
}