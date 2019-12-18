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
 unsigned int INVALID_REGNUM ; 
 scalar_t__ current_function_is_leaf ; 
 int /*<<< orphan*/  current_function_profile ; 
 int /*<<< orphan*/  ix86_current_function_calls_tls_descriptor ; 
 int /*<<< orphan*/ * regs_ever_live ; 

__attribute__((used)) static unsigned int
ix86_select_alt_pic_regnum (void)
{
  if (current_function_is_leaf && !current_function_profile
      && !ix86_current_function_calls_tls_descriptor)
    {
      int i;
      for (i = 2; i >= 0; --i)
        if (!regs_ever_live[i])
	  return i;
    }

  return INVALID_REGNUM;
}