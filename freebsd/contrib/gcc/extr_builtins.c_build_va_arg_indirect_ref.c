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
 int /*<<< orphan*/  build_fold_indirect_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_mudflap ; 
 int /*<<< orphan*/  mf_mark (int /*<<< orphan*/ ) ; 

tree
build_va_arg_indirect_ref (tree addr)
{
  addr = build_fold_indirect_ref (addr);

  if (flag_mudflap) /* Don't instrument va_arg INDIRECT_REF.  */
    mf_mark (addr);

  return addr;
}