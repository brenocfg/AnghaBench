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
 int /*<<< orphan*/  INTMAX_TYPE ; 
 int /*<<< orphan*/  MODIFIED_WCHAR_TYPE ; 
 int /*<<< orphan*/  PTRDIFF_TYPE ; 
 int /*<<< orphan*/  SIZE_TYPE ; 
 int /*<<< orphan*/  UINTMAX_TYPE ; 
 int /*<<< orphan*/  WINT_TYPE ; 
 int /*<<< orphan*/  builtin_define_with_value (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
c_stddef_cpp_builtins(void)
{
  builtin_define_with_value ("__SIZE_TYPE__", SIZE_TYPE, 0);
  builtin_define_with_value ("__PTRDIFF_TYPE__", PTRDIFF_TYPE, 0);
  builtin_define_with_value ("__WCHAR_TYPE__", MODIFIED_WCHAR_TYPE, 0);
  builtin_define_with_value ("__WINT_TYPE__", WINT_TYPE, 0);
  builtin_define_with_value ("__INTMAX_TYPE__", INTMAX_TYPE, 0);
  builtin_define_with_value ("__UINTMAX_TYPE__", UINTMAX_TYPE, 0);
}