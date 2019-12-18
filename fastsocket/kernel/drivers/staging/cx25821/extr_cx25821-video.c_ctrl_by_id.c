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
struct v4l2_queryctrl {unsigned int id; } ;

/* Variables and functions */
 unsigned int CX25821_CTLS ; 
 struct v4l2_queryctrl const* cx25821_ctls ; 

__attribute__((used)) static const struct v4l2_queryctrl *ctrl_by_id(unsigned int id)
{
	unsigned int i;

	for (i = 0; i < CX25821_CTLS; i++)
		if (cx25821_ctls[i].id == id)
			return cx25821_ctls + i;
	return NULL;
}