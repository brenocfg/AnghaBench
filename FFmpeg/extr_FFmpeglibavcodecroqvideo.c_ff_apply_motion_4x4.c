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
typedef  int /*<<< orphan*/  RoqContext ;

/* Variables and functions */
 int /*<<< orphan*/  apply_motion_generic (int /*<<< orphan*/ *,int,int,int,int,int) ; 

void ff_apply_motion_4x4(RoqContext *ri, int x, int y,
                             int deltax, int deltay)
{
    apply_motion_generic(ri, x, y, deltax, deltay, 4);
}