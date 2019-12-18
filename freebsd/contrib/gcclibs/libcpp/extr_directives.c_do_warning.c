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
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_WARNING_SYSHDR ; 
 int /*<<< orphan*/  do_diagnostic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
do_warning (cpp_reader *pfile)
{
  /* We want #warning diagnostics to be emitted in system headers too.  */
  do_diagnostic (pfile, CPP_DL_WARNING_SYSHDR, 1);
}