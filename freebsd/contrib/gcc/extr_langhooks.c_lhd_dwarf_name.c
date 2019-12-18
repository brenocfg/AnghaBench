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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {char const* (* decl_printable_name ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 char const* stub1 (int /*<<< orphan*/ ,int) ; 

const char *
lhd_dwarf_name (tree t, int verbosity)
{
  gcc_assert (DECL_P (t));

  return lang_hooks.decl_printable_name (t, verbosity);
}