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
 scalar_t__ innermost_scope_kind () ; 
 scalar_t__ sk_template_parms ; 

bool
template_parm_scope_p (void)
{
  return innermost_scope_kind () == sk_template_parms;
}