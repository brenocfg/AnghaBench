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
struct v4l2_queryctrl {int id; } ;

/* Variables and functions */
 int NUM_CONTROLS ; 
 struct v4l2_queryctrl* controls ; 

__attribute__((used)) static struct v4l2_queryctrl* ctrl_by_id(int id)
{
	int i;

	for (i = 0; i < NUM_CONTROLS; i++)
		if (controls[i].id == id)
			return controls+i;
	return NULL;
}