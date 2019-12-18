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
struct objfile {int /*<<< orphan*/ * sym_stab_info; int /*<<< orphan*/  md; } ;
struct header_file {struct header_file* vector; struct header_file* name; } ;

/* Variables and functions */
 struct header_file* HEADER_FILES (struct objfile*) ; 
 int N_HEADER_FILES (struct objfile*) ; 
 int /*<<< orphan*/  free_header_files () ; 
 int /*<<< orphan*/  xfree (struct header_file*) ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbx_symfile_finish (struct objfile *objfile)
{
  if (objfile->sym_stab_info != NULL)
    {
      if (HEADER_FILES (objfile) != NULL)
	{
	  int i = N_HEADER_FILES (objfile);
	  struct header_file *hfiles = HEADER_FILES (objfile);

	  while (--i >= 0)
	    {
	      xfree (hfiles[i].name);
	      xfree (hfiles[i].vector);
	    }
	  xfree (hfiles);
	}
      xmfree (objfile->md, objfile->sym_stab_info);
    }
  free_header_files ();
}