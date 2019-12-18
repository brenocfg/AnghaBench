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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int ypan ; 

__attribute__((used)) static int param_set_scroll(const char *val, struct kernel_param *kp)
{
	ypan = 0;

	if (!strcmp(val, "redraw"))
		ypan = 0;
	else if (!strcmp(val, "ypan"))
		ypan = 1;
	else if (!strcmp(val, "ywrap"))
		ypan = 2;
	else
		return -EINVAL;

	return 0;
}