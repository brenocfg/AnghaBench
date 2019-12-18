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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ DECL_GLOBAL_CTOR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_GLOBAL_DTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  input_filename ; 
 int /*<<< orphan*/  pp_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_printf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_global_iord (tree t)
{
  const char *p = NULL;

  if (DECL_GLOBAL_CTOR_P (t))
    p = "initializers";
  else if (DECL_GLOBAL_DTOR_P (t))
    p = "destructors";
  else
    gcc_unreachable ();

  pp_printf (pp_base (cxx_pp), "(static %s for %s)", p, input_filename);
}