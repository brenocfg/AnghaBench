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
 int ARRAY_SIZE (struct v4l2_queryctrl const*) ; 
 struct v4l2_queryctrl const* bttv_ctls ; 

__attribute__((used)) static const struct v4l2_queryctrl *ctrl_by_id(int id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(bttv_ctls); i++)
		if (bttv_ctls[i].id == id)
			return bttv_ctls+i;

	return NULL;
}