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
struct gcov_info {scalar_t__ functions; } ;
struct gcov_fn_info {int dummy; } ;

/* Variables and functions */
 unsigned int get_fn_size (struct gcov_info*) ; 

__attribute__((used)) static struct gcov_fn_info *get_fn_info(struct gcov_info *info, unsigned int fn)
{
	return (struct gcov_fn_info *)
		((char *) info->functions + fn * get_fn_size(info));
}