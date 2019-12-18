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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  simplify_gen_subreg (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreg_lowpart_offset (int,int) ; 

rtx
lowpart_subreg (enum machine_mode outer_mode, rtx expr,
		enum machine_mode inner_mode)
{
  return simplify_gen_subreg (outer_mode, expr, inner_mode,
			      subreg_lowpart_offset (outer_mode, inner_mode));
}