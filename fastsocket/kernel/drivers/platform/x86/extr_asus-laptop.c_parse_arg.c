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

/* Variables and functions */
 int EINVAL ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static int parse_arg(const char *buf, unsigned long count, int *val)
{
	if (!count)
		return 0;
	if (count > 31)
		return -EINVAL;
	if (sscanf(buf, "%i", val) != 1)
		return -EINVAL;
	return count;
}