#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_4__ {scalar_t__ cplusplus; scalar_t__ objc; } ;
typedef  TYPE_1__ cpp_options ;
struct TYPE_5__ {int /*<<< orphan*/  (* extra_includes ) (char const*,char const*,int) ;int /*<<< orphan*/  (* extra_pre_includes ) (char const*,char const*,int) ;} ;

/* Variables and functions */
 size_t BRACKET ; 
 size_t QUOTE ; 
 size_t SYSTEM ; 
 int /*<<< orphan*/  add_env_var_paths (char const* const,size_t) ; 
 int /*<<< orphan*/  add_standard_paths (char const*,char const*,char const*,int) ; 
 TYPE_1__* cpp_get_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpp_set_include_chains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heads ; 
 int /*<<< orphan*/  merge_include_chains (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  quote_ignores_source_dir ; 
 int /*<<< orphan*/  stub1 (char const*,char const*,int) ; 
 int /*<<< orphan*/  stub2 (char const*,char const*,int) ; 
 TYPE_2__ target_c_incpath ; 

void
register_include_chains (cpp_reader *pfile, const char *sysroot,
			 const char *iprefix, const char *imultilib,
			 int stdinc, int cxx_stdinc, int verbose)
{
  static const char *const lang_env_vars[] =
    { "C_INCLUDE_PATH", "CPLUS_INCLUDE_PATH",
      "OBJC_INCLUDE_PATH", "OBJCPLUS_INCLUDE_PATH" };
  cpp_options *cpp_opts = cpp_get_options (pfile);
  size_t idx = (cpp_opts->objc ? 2: 0);

  if (cpp_opts->cplusplus)
    idx++;
  else
    cxx_stdinc = false;

  /* CPATH and language-dependent environment variables may add to the
     include chain.  */
  add_env_var_paths ("CPATH", BRACKET);
  add_env_var_paths (lang_env_vars[idx], SYSTEM);

  target_c_incpath.extra_pre_includes (sysroot, iprefix, stdinc);

  /* Finally chain on the standard directories.  */
  if (stdinc)
    add_standard_paths (sysroot, iprefix, imultilib, cxx_stdinc);

  target_c_incpath.extra_includes (sysroot, iprefix, stdinc);

  merge_include_chains (pfile, verbose);

  cpp_set_include_chains (pfile, heads[QUOTE], heads[BRACKET],
			  quote_ignores_source_dir);
}