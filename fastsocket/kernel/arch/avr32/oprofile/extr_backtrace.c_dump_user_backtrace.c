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
struct frame_head {struct frame_head* fp; int /*<<< orphan*/  lr; } ;
typedef  int /*<<< orphan*/  bufhead ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_READ ; 
 scalar_t__ __copy_from_user_inatomic (struct frame_head*,struct frame_head*,int) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,struct frame_head*,int) ; 
 int /*<<< orphan*/  oprofile_add_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct frame_head *dump_user_backtrace(struct frame_head *head)
{
	struct frame_head bufhead[2];

	/* Also check accessibility of one struct frame_head beyond */
	if (!access_ok(VERIFY_READ, head, sizeof(bufhead)))
		return NULL;
	if (__copy_from_user_inatomic(bufhead, head, sizeof(bufhead)))
		return NULL;

	oprofile_add_trace(bufhead[0].lr);

	/* frame pointers should strictly progress back up the stack
	 * (towards higher addresses) */
	if (bufhead[0].fp <= head)
		return NULL;

	return bufhead[0].fp;
}