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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DLL_EXPORT_PREFIX ; 
 int /*<<< orphan*/  DLL_IMPORT_PREFIX ; 
 char const FASTCALL_PREFIX ; 
 char* USER_LABEL_PREFIX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* i386_pe_strip_name_encoding (char const*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

void i386_pe_output_labelref (FILE *stream, const char *name)
{
  if (strncmp (name, DLL_IMPORT_PREFIX, strlen (DLL_IMPORT_PREFIX))
      == 0)
    /* A dll import */
    {
      if (name[strlen (DLL_IMPORT_PREFIX)] == FASTCALL_PREFIX)
      /* A dllimport fastcall symbol.  */
        {
          fprintf (stream, "__imp_%s",
                   i386_pe_strip_name_encoding (name));
        }
      else
      /* A dllimport non-fastcall symbol.  */
        {
          fprintf (stream, "__imp__%s",
                   i386_pe_strip_name_encoding (name));
        }
    }
  else if ((name[0] == FASTCALL_PREFIX)
           || (strncmp (name, DLL_EXPORT_PREFIX, strlen (DLL_EXPORT_PREFIX))
	       == 0
	       && name[strlen (DLL_EXPORT_PREFIX)] == FASTCALL_PREFIX))
    /* A fastcall symbol.  */
    {
      fprintf (stream, "%s",
               i386_pe_strip_name_encoding (name));
    }
  else
    /* Everything else.  */
    {
      fprintf (stream, "%s%s", USER_LABEL_PREFIX,
               i386_pe_strip_name_encoding (name));
    }
}