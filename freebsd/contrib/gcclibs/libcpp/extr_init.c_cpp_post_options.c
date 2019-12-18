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
 scalar_t__ CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cplusplus ; 
 int /*<<< orphan*/  mark_named_operators (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  operator_names ; 
 int /*<<< orphan*/  post_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sanity_checks (int /*<<< orphan*/ *) ; 

void
cpp_post_options (cpp_reader *pfile)
{
  sanity_checks (pfile);

  post_options (pfile);

  /* Mark named operators before handling command line macros.  */
  if (CPP_OPTION (pfile, cplusplus) && CPP_OPTION (pfile, operator_names))
    mark_named_operators (pfile);
}