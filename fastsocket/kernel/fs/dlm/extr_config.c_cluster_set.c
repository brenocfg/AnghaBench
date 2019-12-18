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
struct dlm_cluster {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cluster_set(struct dlm_cluster *cl, unsigned int *cl_field,
			   int *info_field, int check_zero,
			   const char *buf, size_t len)
{
	unsigned int x;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	x = simple_strtoul(buf, NULL, 0);

	if (check_zero && !x)
		return -EINVAL;

	*cl_field = x;
	*info_field = x;

	return len;
}