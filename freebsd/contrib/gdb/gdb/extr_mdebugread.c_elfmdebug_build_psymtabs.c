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
struct objfile {int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/ * obfd; } ;
struct ecoff_debug_swap {int /*<<< orphan*/  (* read_debug_info ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ecoff_debug_info*) ;} ;
struct ecoff_debug_info {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_minimal_symbol_collection () ; 
 int /*<<< orphan*/  install_minimal_symbols (struct objfile*) ; 
 struct cleanup* make_cleanup_discard_minimal_symbols () ; 
 int /*<<< orphan*/  mdebug_build_psymtabs (struct objfile*,struct ecoff_debug_swap const*,struct ecoff_debug_info*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ecoff_debug_info*) ; 

void
elfmdebug_build_psymtabs (struct objfile *objfile,
			  const struct ecoff_debug_swap *swap, asection *sec)
{
  bfd *abfd = objfile->obfd;
  struct ecoff_debug_info *info;
  struct cleanup *back_to;

  /* FIXME: It's not clear whether we should be getting minimal symbol
     information from .mdebug in an ELF file, or whether we will.
     Re-initialize the minimal symbol reader in case we do.  */

  init_minimal_symbol_collection ();
  back_to = make_cleanup_discard_minimal_symbols ();

  info = ((struct ecoff_debug_info *)
	  obstack_alloc (&objfile->objfile_obstack,
			 sizeof (struct ecoff_debug_info)));

  if (!(*swap->read_debug_info) (abfd, sec, info))
    error ("Error reading ECOFF debugging information: %s",
	   bfd_errmsg (bfd_get_error ()));

  mdebug_build_psymtabs (objfile, swap, info);

  install_minimal_symbols (objfile);
  do_cleanups (back_to);
}