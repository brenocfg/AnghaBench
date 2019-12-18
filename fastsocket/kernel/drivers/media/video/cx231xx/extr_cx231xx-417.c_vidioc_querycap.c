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
struct v4l2_capability {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct v4l2_capability*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvr_capability ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
				struct v4l2_capability *cap)
{



		memcpy(cap, &pvr_capability, sizeof(struct v4l2_capability));
	return 0;
}