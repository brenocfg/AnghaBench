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
typedef  scalar_t__ s32_t ;

/* Variables and functions */

__attribute__((used)) static s32_t bt_mesh_ceiling(float num)
{
    s32_t inum = (s32_t)num;

    if (num == (float)inum) {
        return inum;
    }

    return inum + 1;
}