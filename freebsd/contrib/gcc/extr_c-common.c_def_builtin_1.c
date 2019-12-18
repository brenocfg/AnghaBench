#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;
typedef  enum built_in_class { ____Placeholder_built_in_class } built_in_class ;
struct TYPE_2__ {scalar_t__ (* builtin_function ) (char const*,scalar_t__,int,int,char const*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__* built_in_decls ; 
 int /*<<< orphan*/  builtin_function_disabled_p (char const*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  flag_no_builtin ; 
 scalar_t__ flag_no_nonansi_builtin ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__* implicit_built_in_decls ; 
 TYPE_1__ lang_hooks ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 scalar_t__ stub1 (char const*,scalar_t__,int,int,char const*,scalar_t__) ; 
 scalar_t__ stub2 (char const*,scalar_t__,int,int,char const*,scalar_t__) ; 

__attribute__((used)) static void
def_builtin_1 (enum built_in_function fncode,
	       const char *name,
	       enum built_in_class fnclass,
	       tree fntype, tree libtype,
	       bool both_p, bool fallback_p, bool nonansi_p,
	       tree fnattrs, bool implicit_p)
{
  tree decl;
  const char *libname;

  if (fntype == error_mark_node)
    return;

  gcc_assert ((!both_p && !fallback_p)
	      || !strncmp (name, "__builtin_",
			   strlen ("__builtin_")));

  libname = name + strlen ("__builtin_");
  decl = lang_hooks.builtin_function (name, fntype, fncode, fnclass,
				      (fallback_p ? libname : NULL),
				      fnattrs);
  if (both_p
      && !flag_no_builtin && !builtin_function_disabled_p (libname)
      && !(nonansi_p && flag_no_nonansi_builtin))
    lang_hooks.builtin_function (libname, libtype, fncode, fnclass,
				 NULL, fnattrs);

  built_in_decls[(int) fncode] = decl;
  if (implicit_p)
    implicit_built_in_decls[(int) fncode] = decl;
}