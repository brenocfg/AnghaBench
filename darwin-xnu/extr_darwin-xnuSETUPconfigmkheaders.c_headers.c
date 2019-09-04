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
struct file_list {scalar_t__ f_needs; struct file_list* f_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_count (scalar_t__,scalar_t__,int) ; 
 struct file_list* ftab ; 

void
headers(void)
{
	struct file_list *fl;

	for (fl = ftab; fl != 0; fl = fl->f_next)
		if (fl->f_needs != 0)
			do_count(fl->f_needs, fl->f_needs, 1);
}