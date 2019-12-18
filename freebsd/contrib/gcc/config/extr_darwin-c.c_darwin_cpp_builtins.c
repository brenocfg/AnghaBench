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
 int /*<<< orphan*/  builtin_define (char*) ; 
 int /*<<< orphan*/  builtin_define_with_value (char*,char*,int) ; 
 scalar_t__ darwin_macosx_version_min ; 
 char* version_as_macro () ; 

void
darwin_cpp_builtins (cpp_reader *pfile)
{
  builtin_define ("__MACH__");
  builtin_define ("__APPLE__");

  /* __APPLE_CC__ is defined as some old Apple include files expect it
     to be defined and won't work if it isn't.  */
  builtin_define_with_value ("__APPLE_CC__", "1", false);

  if (darwin_macosx_version_min)
    builtin_define_with_value ("__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__",
			       version_as_macro(), false);
}