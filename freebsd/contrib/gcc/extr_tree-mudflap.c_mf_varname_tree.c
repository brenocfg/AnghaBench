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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  pretty_printer ;
struct TYPE_4__ {unsigned int line; unsigned int column; char* file; } ;
typedef  TYPE_1__ expanded_location ;
struct TYPE_5__ {char* (* decl_printable_name ) (scalar_t__,int) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DECL_NAME (scalar_t__) ; 
 char* DECL_SOURCE_FILE (scalar_t__) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (scalar_t__) ; 
 int DMGL_AUTO ; 
 int DMGL_VERBOSE ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ *) ; 
 scalar_t__ NULL_TREE ; 
 char* cplus_demangle (int /*<<< orphan*/ ,int) ; 
 scalar_t__ current_function_decl ; 
 TYPE_1__ expand_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 scalar_t__ mf_build_string (char const*) ; 
 char* pp_base_formatted_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_clear_output_area (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_decimal_int (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* stub1 (scalar_t__,int) ; 
 char* stub2 (scalar_t__,int) ; 

__attribute__((used)) static tree
mf_varname_tree (tree decl)
{
  static pretty_printer buf_rec;
  static int initialized = 0;
  pretty_printer *buf = & buf_rec;
  const char *buf_contents;
  tree result;

  gcc_assert (decl);

  if (!initialized)
    {
      pp_construct (buf, /* prefix */ NULL, /* line-width */ 0);
      initialized = 1;
    }
  pp_clear_output_area (buf);

  /* Add FILENAME[:LINENUMBER[:COLUMNNUMBER]].  */
  {
    expanded_location xloc = expand_location (DECL_SOURCE_LOCATION (decl));
    const char *sourcefile;
    unsigned sourceline = xloc.line;
    unsigned sourcecolumn = 0;
#ifdef USE_MAPPED_LOCATION
    sourcecolumn = xloc.column;
#endif
    sourcefile = xloc.file;
    if (sourcefile == NULL && current_function_decl != NULL_TREE)
      sourcefile = DECL_SOURCE_FILE (current_function_decl);
    if (sourcefile == NULL)
      sourcefile = "<unknown file>";

    pp_string (buf, sourcefile);

    if (sourceline != 0)
      {
        pp_string (buf, ":");
        pp_decimal_int (buf, sourceline);

        if (sourcecolumn != 0)
          {
            pp_string (buf, ":");
            pp_decimal_int (buf, sourcecolumn);
          }
      }
  }

  if (current_function_decl != NULL_TREE)
    {
      /* Add (FUNCTION) */
      pp_string (buf, " (");
      {
        const char *funcname = NULL;
        if (DECL_NAME (current_function_decl))
          funcname = lang_hooks.decl_printable_name (current_function_decl, 1);
        if (funcname == NULL)
          funcname = "anonymous fn";

        pp_string (buf, funcname);
      }
      pp_string (buf, ") ");
    }
  else
    pp_string (buf, " ");

  /* Add <variable-declaration>, possibly demangled.  */
  {
    const char *declname = NULL;

    if (DECL_NAME (decl) != NULL)
      {
	if (strcmp ("GNU C++", lang_hooks.name) == 0)
	  {
	    /* The gcc/cp decl_printable_name hook doesn't do as good a job as
	       the libiberty demangler.  */
	    declname = cplus_demangle (IDENTIFIER_POINTER (DECL_NAME (decl)),
				       DMGL_AUTO | DMGL_VERBOSE);
	  }
	if (declname == NULL)
	  declname = lang_hooks.decl_printable_name (decl, 3);
      }
    if (declname == NULL)
      declname = "<unnamed variable>";

    pp_string (buf, declname);
  }

  /* Return the lot as a new STRING_CST.  */
  buf_contents = pp_base_formatted_text (buf);
  result = mf_build_string (buf_contents);
  pp_clear_output_area (buf);

  return result;
}