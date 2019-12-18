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
struct tomoyo_io_buffer {int read_eof; int read_step; int /*<<< orphan*/ * read_var2; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tomoyo_read_alias_policy (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_read_domain_initializer_policy (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_read_domain_keeper_policy (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_read_file_pattern (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_read_globally_readable_policy (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  tomoyo_read_no_rewrite_policy (struct tomoyo_io_buffer*) ; 

__attribute__((used)) static int tomoyo_read_exception_policy(struct tomoyo_io_buffer *head)
{
	if (!head->read_eof) {
		switch (head->read_step) {
		case 0:
			head->read_var2 = NULL;
			head->read_step = 1;
		case 1:
			if (!tomoyo_read_domain_keeper_policy(head))
				break;
			head->read_var2 = NULL;
			head->read_step = 2;
		case 2:
			if (!tomoyo_read_globally_readable_policy(head))
				break;
			head->read_var2 = NULL;
			head->read_step = 3;
		case 3:
			head->read_var2 = NULL;
			head->read_step = 4;
		case 4:
			if (!tomoyo_read_domain_initializer_policy(head))
				break;
			head->read_var2 = NULL;
			head->read_step = 5;
		case 5:
			if (!tomoyo_read_alias_policy(head))
				break;
			head->read_var2 = NULL;
			head->read_step = 6;
		case 6:
			head->read_var2 = NULL;
			head->read_step = 7;
		case 7:
			if (!tomoyo_read_file_pattern(head))
				break;
			head->read_var2 = NULL;
			head->read_step = 8;
		case 8:
			if (!tomoyo_read_no_rewrite_policy(head))
				break;
			head->read_var2 = NULL;
			head->read_step = 9;
		case 9:
			head->read_eof = true;
			break;
		default:
			return -EINVAL;
		}
	}
	return 0;
}