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
 scalar_t__ CLK_ASM ; 
 scalar_t__ CLK_STDC94 ; 
 scalar_t__ CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_define_builtin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  c99 ; 
 int /*<<< orphan*/  cplusplus ; 
 int /*<<< orphan*/  cpp_init_special_builtins (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang ; 
 int /*<<< orphan*/  objc ; 
 int /*<<< orphan*/  std ; 
 int /*<<< orphan*/  stdc_0_in_system_headers ; 
 int /*<<< orphan*/  traditional ; 

void
cpp_init_builtins (cpp_reader *pfile, int hosted)
{
  cpp_init_special_builtins (pfile);

  if (!CPP_OPTION (pfile, traditional)
      && (! CPP_OPTION (pfile, stdc_0_in_system_headers)
	  || CPP_OPTION (pfile, std)))
    _cpp_define_builtin (pfile, "__STDC__ 1");

  if (CPP_OPTION (pfile, cplusplus))
    _cpp_define_builtin (pfile, "__cplusplus 1");
  else if (CPP_OPTION (pfile, lang) == CLK_ASM)
    _cpp_define_builtin (pfile, "__ASSEMBLER__ 1");
  else if (CPP_OPTION (pfile, lang) == CLK_STDC94)
    _cpp_define_builtin (pfile, "__STDC_VERSION__ 199409L");
  else if (CPP_OPTION (pfile, c99))
    _cpp_define_builtin (pfile, "__STDC_VERSION__ 199901L");

  if (hosted)
    _cpp_define_builtin (pfile, "__STDC_HOSTED__ 1");
  else
    _cpp_define_builtin (pfile, "__STDC_HOSTED__ 0");

  if (CPP_OPTION (pfile, objc))
    _cpp_define_builtin (pfile, "__OBJC__ 1");
}