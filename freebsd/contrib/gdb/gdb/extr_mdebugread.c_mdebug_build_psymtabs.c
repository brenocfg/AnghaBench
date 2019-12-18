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
struct objfile {int /*<<< orphan*/  name; int /*<<< orphan*/  obfd; int /*<<< orphan*/  objfile_obstack; } ;
struct ecoff_debug_swap {int external_fdr_size; int /*<<< orphan*/  (* swap_fdr_in ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {int ifdMax; } ;
struct ecoff_debug_info {char* external_fdr; int /*<<< orphan*/ * fdr; TYPE_1__ symbolic_header; } ;
typedef  int /*<<< orphan*/  FDR ;

/* Variables and functions */
 int /*<<< orphan*/  GLEVEL_2 ; 
 int /*<<< orphan*/  buildsym_new_init () ; 
 scalar_t__ compare_glevel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cur_bfd ; 
 struct ecoff_debug_info* debug_info ; 
 struct ecoff_debug_swap const* debug_swap ; 
 int /*<<< orphan*/  free_header_files () ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  init_header_files () ; 
 scalar_t__ max_gdbinfo ; 
 int /*<<< orphan*/  max_glevel ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parse_partial_symbols (struct objfile*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  stabsread_new_init () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
mdebug_build_psymtabs (struct objfile *objfile,
		       const struct ecoff_debug_swap *swap,
		       struct ecoff_debug_info *info)
{
  cur_bfd = objfile->obfd;
  debug_swap = swap;
  debug_info = info;

  stabsread_new_init ();
  buildsym_new_init ();
  free_header_files ();
  init_header_files ();
        
  /* Make sure all the FDR information is swapped in.  */
  if (info->fdr == (FDR *) NULL)
    {
      char *fdr_src;
      char *fdr_end;
      FDR *fdr_ptr;

      info->fdr = (FDR *) obstack_alloc (&objfile->objfile_obstack,
					 (info->symbolic_header.ifdMax
					  * sizeof (FDR)));
      fdr_src = info->external_fdr;
      fdr_end = (fdr_src
		 + info->symbolic_header.ifdMax * swap->external_fdr_size);
      fdr_ptr = info->fdr;
      for (; fdr_src < fdr_end; fdr_src += swap->external_fdr_size, fdr_ptr++)
	(*swap->swap_fdr_in) (objfile->obfd, fdr_src, fdr_ptr);
    }

  parse_partial_symbols (objfile);

#if 0
  /* Check to make sure file was compiled with -g.  If not, warn the
     user of this limitation.  */
  if (compare_glevel (max_glevel, GLEVEL_2) < 0)
    {
      if (max_gdbinfo == 0)
	printf_unfiltered ("\n%s not compiled with -g, debugging support is limited.\n",
			   objfile->name);
      printf_unfiltered ("You should compile with -g2 or -g3 for best debugging support.\n");
      gdb_flush (gdb_stdout);
    }
#endif
}