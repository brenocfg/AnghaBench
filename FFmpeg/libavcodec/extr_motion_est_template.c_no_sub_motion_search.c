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
typedef  int /*<<< orphan*/  MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static int no_sub_motion_search(MpegEncContext * s,
          int *mx_ptr, int *my_ptr, int dmin,
                                  int src_index, int ref_index,
                                  int size, int h)
{
    (*mx_ptr)<<=1;
    (*my_ptr)<<=1;
    return dmin;
}