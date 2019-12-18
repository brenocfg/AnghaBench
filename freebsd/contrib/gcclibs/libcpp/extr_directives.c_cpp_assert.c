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
 int /*<<< orphan*/  T_ASSERT ; 
 int /*<<< orphan*/  handle_assertion (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void
cpp_assert (cpp_reader *pfile, const char *str)
{
  handle_assertion (pfile, str, T_ASSERT);
}