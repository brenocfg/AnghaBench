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
typedef  enum lc_reason { ____Placeholder_lc_reason } lc_reason ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  _cpp_do_file_change (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 

void
cpp_change_file (cpp_reader *pfile, enum lc_reason reason,
		 const char *new_name)
{
  _cpp_do_file_change (pfile, reason, new_name, 1, 0);
}