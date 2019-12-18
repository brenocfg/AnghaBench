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
 int mid_pred (int,int,int) ; 

__attribute__((used)) static int get_cmy_scale(int r, int g, int b, int min_val, int max_val)
{
    return mid_pred(r, g, b) - min_val;
}