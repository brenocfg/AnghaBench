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
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 int pp_indentation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

void
pp_base_indent (pretty_printer *pp)
{
  int n = pp_indentation (pp);
  int i;

  for (i = 0; i < n; ++i)
    pp_space (pp);
}