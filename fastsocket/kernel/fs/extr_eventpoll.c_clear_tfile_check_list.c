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
struct tfile_check {struct tfile_check* next; scalar_t__ count; } ;

/* Variables and functions */
 struct tfile_check base_tfile_check ; 
 int /*<<< orphan*/  clear_added_flag (struct tfile_check*) ; 
 struct tfile_check* current_tfile_check ; 
 int /*<<< orphan*/  kfree (struct tfile_check*) ; 

void clear_tfile_check_list(void)
{
	struct tfile_check *tfile_check_iter, *tmp;

	tfile_check_iter = base_tfile_check.next;
	base_tfile_check.next = NULL;
	clear_added_flag(&base_tfile_check);
	base_tfile_check.count = 0;

	while (tfile_check_iter) {
		clear_added_flag(tfile_check_iter);
		tmp = tfile_check_iter;
		tfile_check_iter = tfile_check_iter->next;
		kfree(tmp);
	}
	current_tfile_check = &base_tfile_check;
}