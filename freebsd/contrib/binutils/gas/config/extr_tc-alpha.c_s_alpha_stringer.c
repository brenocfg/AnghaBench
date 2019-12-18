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

/* Variables and functions */
 scalar_t__ alpha_current_align ; 
 int /*<<< orphan*/ * alpha_insn_label ; 
 int /*<<< orphan*/  stringer (int) ; 

__attribute__((used)) static void
s_alpha_stringer (int terminate)
{
  alpha_current_align = 0;
  alpha_insn_label = NULL;
  stringer (terminate);
}