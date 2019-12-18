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
 int do_search_boundary (int,int,int,int) ; 

__attribute__((used)) static int search_boundary(int plane_boundary, int search_range, int search_step, int vertical, int y, int x)
{
    return do_search_boundary(vertical ? y : x, plane_boundary, search_range, search_step);
}