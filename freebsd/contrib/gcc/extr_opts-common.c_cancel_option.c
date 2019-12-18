#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int neg_index; } ;

/* Variables and functions */
 TYPE_1__* cl_options ; 

__attribute__((used)) static bool
cancel_option (int opt_idx, int next_opt_idx, int orig_next_opt_idx)
{
  /* An option can be canceled by the same option or an option with
     Negative.  */
  if (cl_options [next_opt_idx].neg_index == opt_idx)
    return true;

  if (cl_options [next_opt_idx].neg_index != orig_next_opt_idx)
    return cancel_option (opt_idx, cl_options [next_opt_idx].neg_index,
			  orig_next_opt_idx);
    
  return false;
}