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
 int MAX_HWIFS ; 
 int ide_ignore_cable ; 
 int sscanf (char const*,char*,int*,...) ; 

__attribute__((used)) static int ide_set_ignore_cable(const char *s, struct kernel_param *kp)
{
	int i, j = 1;

	/* controller (ignore) */
	/* controller : 1 (ignore) | 0 (use) */
	if (sscanf(s, "%d:%d", &i, &j) != 2 && sscanf(s, "%d", &i) != 1)
		return -EINVAL;

	if (i >= MAX_HWIFS || j < 0 || j > 1)
		return -EINVAL;

	if (j)
		ide_ignore_cable |= (1 << i);
	else
		ide_ignore_cable &= ~(1 << i);

	return 0;
}