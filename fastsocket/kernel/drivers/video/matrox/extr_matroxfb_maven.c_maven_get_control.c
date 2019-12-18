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
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct maven_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_ctrl_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_ctrl_ptr (struct maven_data*,int) ; 

__attribute__((used)) static int maven_get_control (struct maven_data* md, 
			      struct v4l2_control *p) {
	int i;
	
	i = get_ctrl_id(p->id);
	if (i < 0) return -EINVAL;
	p->value = *get_ctrl_ptr(md, i);
	return 0;
}