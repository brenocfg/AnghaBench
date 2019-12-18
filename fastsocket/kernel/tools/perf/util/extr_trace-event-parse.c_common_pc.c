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
struct scripting_context {int dummy; } ;

/* Variables and functions */
 int get_common_field (struct scripting_context*,int*,int*,char*) ; 

int common_pc(struct scripting_context *context)
{
	static int offset;
	static int size;
	int ret;

	ret = get_common_field(context, &size, &offset,
			       "common_preempt_count");
	if (ret < 0)
		return -1;

	return ret;
}