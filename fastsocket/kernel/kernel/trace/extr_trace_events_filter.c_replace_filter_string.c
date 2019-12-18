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
struct event_filter {int /*<<< orphan*/  filter_string; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int replace_filter_string(struct event_filter *filter,
				 char *filter_string)
{
	kfree(filter->filter_string);
	filter->filter_string = kstrdup(filter_string, GFP_KERNEL);
	if (!filter->filter_string)
		return -ENOMEM;

	return 0;
}