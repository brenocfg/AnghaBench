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
struct vml_sys {int dummy; } ;

/* Variables and functions */
 int* crvml_clocks ; 
 size_t crvml_nearest_index (struct vml_sys const*,int) ; 

__attribute__((used)) static int crvml_nearest_clock(const struct vml_sys *sys, int clock)
{
	return crvml_clocks[crvml_nearest_index(sys, clock)];
}