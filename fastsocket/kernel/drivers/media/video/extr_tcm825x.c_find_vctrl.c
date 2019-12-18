#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; } ;
struct vcontrol {TYPE_1__ qc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vcontrol*) ; 
 int V4L2_CID_BASE ; 
 struct vcontrol* video_control ; 

__attribute__((used)) static struct vcontrol *find_vctrl(int id)
{
	int i;

	if (id < V4L2_CID_BASE)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(video_control); i++)
		if (video_control[i].qc.id == id)
			return &video_control[i];

	return NULL;
}