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
typedef  char const* tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* decl_printable_name ) (scalar_t__,int) ;} ;

/* Variables and functions */
 scalar_t__ DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  OPT_Wformat ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 char* TYPE_MAIN_VARIANT (char const*) ; 
 scalar_t__ TYPE_NAME (char const*) ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ c_dialect_cxx () ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
format_type_warning (const char *descr, const char *format_start,
		     int format_length, tree wanted_type, int pointer_count,
		     const char *wanted_type_name, tree arg_type, int arg_num)
{
  char *p;
  /* If ARG_TYPE is a typedef with a misleading name (for example,
     size_t but not the standard size_t expected by printf %zu), avoid
     printing the typedef name.  */
  if (wanted_type_name
      && TYPE_NAME (arg_type)
      && TREE_CODE (TYPE_NAME (arg_type)) == TYPE_DECL
      && DECL_NAME (TYPE_NAME (arg_type))
      && !strcmp (wanted_type_name,
		  lang_hooks.decl_printable_name (TYPE_NAME (arg_type), 2)))
    arg_type = TYPE_MAIN_VARIANT (arg_type);
  /* The format type and name exclude any '*' for pointers, so those
     must be formatted manually.  For all the types we currently have,
     this is adequate, but formats taking pointers to functions or
     arrays would require the full type to be built up in order to
     print it with %T.  */
  p = (char *) alloca (pointer_count + 2);
  if (pointer_count == 0)
    p[0] = 0;
  else if (c_dialect_cxx ())
    {
      memset (p, '*', pointer_count);
      p[pointer_count] = 0;
    }
  else
    {
      p[0] = ' ';
      memset (p + 1, '*', pointer_count);
      p[pointer_count + 1] = 0;
    }
  if (wanted_type_name)
    {
      if (descr)
	warning (OPT_Wformat, "%s should have type %<%s%s%>, "
		 "but argument %d has type %qT",
		 descr, wanted_type_name, p, arg_num, arg_type);
      else
	warning (OPT_Wformat, "format %q.*s expects type %<%s%s%>, "
		 "but argument %d has type %qT",
		 format_length, format_start, wanted_type_name, p,
		 arg_num, arg_type);
    }
  else
    {
      if (descr)
	warning (OPT_Wformat, "%s should have type %<%T%s%>, "
		 "but argument %d has type %qT",
		 descr, wanted_type, p, arg_num, arg_type);
      else
	warning (OPT_Wformat, "format %q.*s expects type %<%T%s%>, "
		 "but argument %d has type %qT",
		 format_length, format_start, wanted_type, p, arg_num, arg_type);
    }
}