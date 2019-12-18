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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  location_t ;
struct TYPE_4__ {char* file; scalar_t__ line; scalar_t__ column; } ;
typedef  TYPE_1__ expanded_location ;
struct TYPE_5__ {char* (* decl_printable_name ) (scalar_t__,int) ;} ;

/* Variables and functions */
 char* DECL_SOURCE_FILE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 char* concat (char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ current_function_decl ; 
 TYPE_1__ expand_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  mf_build_string (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 char* stub1 (scalar_t__,int) ; 

__attribute__((used)) static tree
mf_file_function_line_tree (location_t location)
{
  expanded_location xloc = expand_location (location);
  const char *file = NULL, *colon, *line, *op, *name, *cp;
  char linecolbuf[30]; /* Enough for two decimal numbers plus a colon.  */
  char *string;
  tree result;

  /* Add FILENAME[:LINENUMBER[:COLUMNNUMBER]].  */
  file = xloc.file;
  if (file == NULL && current_function_decl != NULL_TREE)
    file = DECL_SOURCE_FILE (current_function_decl);
  if (file == NULL)
    file = "<unknown file>";

  if (xloc.line > 0)
    {
#ifdef USE_MAPPED_LOCATION
      if (xloc.column > 0)
        sprintf (linecolbuf, "%d:%d", xloc.line, xloc.column);
      else
#endif
        sprintf (linecolbuf, "%d", xloc.line);
      colon = ":";
      line = linecolbuf;
    }
  else
    colon = line = "";

  /* Add (FUNCTION).  */
  name = lang_hooks.decl_printable_name (current_function_decl, 1);
  if (name)
    {
      op = " (";
      cp = ")";
    }
  else
    op = name = cp = "";

  string = concat (file, colon, line, op, name, cp, NULL);
  result = mf_build_string (string);
  free (string);

  return result;
}