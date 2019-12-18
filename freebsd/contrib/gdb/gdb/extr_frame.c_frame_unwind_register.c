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
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  frame_register_unwind (struct frame_info*,int,int*,int*,int /*<<< orphan*/ *,int*,void*) ; 

void
frame_unwind_register (struct frame_info *frame, int regnum, void *buf)
{
  int optimized;
  CORE_ADDR addr;
  int realnum;
  enum lval_type lval;
  frame_register_unwind (frame, regnum, &optimized, &lval, &addr,
			 &realnum, buf);
}