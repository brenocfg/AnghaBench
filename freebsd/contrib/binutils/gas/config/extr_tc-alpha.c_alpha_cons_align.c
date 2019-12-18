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
 int /*<<< orphan*/  alpha_align (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ alpha_auto_align_on ; 
 int alpha_current_align ; 
 int /*<<< orphan*/ * alpha_insn_label ; 

void
alpha_cons_align (int size)
{
  int log_size;

  log_size = 0;
  while ((size >>= 1) != 0)
    ++log_size;

  if (alpha_auto_align_on && alpha_current_align < log_size)
    alpha_align (log_size, (char *) NULL, alpha_insn_label, 0);
  if (alpha_current_align > log_size)
    alpha_current_align = log_size;
  alpha_insn_label = NULL;
}