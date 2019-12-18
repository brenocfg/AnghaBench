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
struct objfile {int dummy; } ;
struct internal_nlist {char* n_strx; } ;

/* Variables and functions */
 int DBX_STRINGTAB (struct objfile*) ; 
 unsigned int DBX_STRINGTAB_SIZE (struct objfile*) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 unsigned int file_string_table_offset ; 
 int /*<<< orphan*/  symfile_complaints ; 
 int /*<<< orphan*/  symnum ; 

__attribute__((used)) static char *
set_namestring (struct objfile *objfile, struct internal_nlist nlist)
{
  char *namestring;

  if (((unsigned) nlist.n_strx + file_string_table_offset) >=
      DBX_STRINGTAB_SIZE (objfile))
    {
      complaint (&symfile_complaints, "bad string table offset in symbol %d",
		 symnum);
      namestring = "<bad string table offset>";
    } 
  else
    namestring = nlist.n_strx + file_string_table_offset +
      DBX_STRINGTAB (objfile);
  return namestring;
}