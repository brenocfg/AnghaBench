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
struct stack_frame {struct stack_frame* next_frame; int /*<<< orphan*/  return_address; } ;
typedef  int /*<<< orphan*/  bufhead ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_READ ; 
 scalar_t__ __copy_from_user_inatomic (struct stack_frame*,struct stack_frame*,int) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,struct stack_frame*,int) ; 
 int /*<<< orphan*/  oprofile_add_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stack_frame *dump_user_backtrace(struct stack_frame *head)
{
	struct stack_frame bufhead[2];

	/* Also check accessibility of one struct stack_frame beyond */
	if (!access_ok(VERIFY_READ, head, sizeof(bufhead)))
		return NULL;
	if (__copy_from_user_inatomic(bufhead, head, sizeof(bufhead)))
		return NULL;

	oprofile_add_trace(bufhead[0].return_address);

	/* frame pointers should strictly progress back up the stack
	 * (towards higher addresses) */
	if (head >= bufhead[0].next_frame)
		return NULL;

	return bufhead[0].next_frame;
}