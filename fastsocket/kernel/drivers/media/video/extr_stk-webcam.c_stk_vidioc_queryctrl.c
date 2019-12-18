#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_queryctrl {scalar_t__ id; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct v4l2_queryctrl*,TYPE_1__*,int) ; 
 TYPE_1__* stk_controls ; 

__attribute__((used)) static int stk_vidioc_queryctrl(struct file *filp,
		void *priv, struct v4l2_queryctrl *c)
{
	int i;
	int nbr;
	nbr = ARRAY_SIZE(stk_controls);

	for (i = 0; i < nbr; i++) {
		if (stk_controls[i].id == c->id) {
			memcpy(c, &stk_controls[i],
				sizeof(struct v4l2_queryctrl));
			return 0;
		}
	}
	return -EINVAL;
}