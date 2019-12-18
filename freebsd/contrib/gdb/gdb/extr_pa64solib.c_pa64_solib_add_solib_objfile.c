#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  linkage_ptr; } ;
struct so_list {TYPE_2__ pa64_solib_desc; TYPE_5__* objfile; int /*<<< orphan*/  abfd; } ;
struct section_addr_info {TYPE_1__* other; } ;
struct cleanup {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  dp; struct so_list* so_info; int /*<<< orphan*/ * unwind_info; } ;
typedef  TYPE_3__ obj_private_data_t ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {scalar_t__ filepos; } ;
typedef  TYPE_4__ asection ;
struct TYPE_13__ {TYPE_3__* obj_private; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  flags; int /*<<< orphan*/  obfd; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  OBJF_SHARED ; 
 struct section_addr_info* alloc_section_addr_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_count_sections (int /*<<< orphan*/ *) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 TYPE_4__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  find_lowest_section ; 
 int /*<<< orphan*/  gnutarget ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct section_addr_info*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 TYPE_5__* symbol_file_add (char*,int,struct section_addr_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
pa64_solib_add_solib_objfile (struct so_list *so, char *name, int from_tty,
			      CORE_ADDR text_addr)
{
  bfd *tmp_bfd;
  asection *sec;
  obj_private_data_t *obj_private;
  struct section_addr_info *section_addrs;
  struct cleanup *my_cleanups;

  /* We need the BFD so that we can look at its sections.  We open up the
     file temporarily, then close it when we are done.  */
  tmp_bfd = bfd_openr (name, gnutarget);
  if (tmp_bfd == NULL)
    {
      perror_with_name (name);
      return;
    }

  if (!bfd_check_format (tmp_bfd, bfd_object))
    {
      bfd_close (tmp_bfd);
      error ("\"%s\" is not an object file: %s", name,
	     bfd_errmsg (bfd_get_error ()));
    }


  /* Undo some braindamage from symfile.c.

     First, symfile.c will subtract the VMA of the first .text section
     in the shared library that it finds.  Undo that.  */
  sec = bfd_get_section_by_name (tmp_bfd, ".text");
  text_addr += bfd_section_vma (tmp_bfd, sec);

  /* Now find the true lowest section in the shared library.  */
  sec = NULL;
  bfd_map_over_sections (tmp_bfd, find_lowest_section, &sec);

  if (sec)
    {
      /* Subtract out the VMA of the lowest section.  */
      text_addr -= bfd_section_vma (tmp_bfd, sec);

      /* ??? Add back in the filepos of that lowest section. */
      text_addr += sec->filepos;
    }

  section_addrs = alloc_section_addr_info (bfd_count_sections (tmp_bfd));
  my_cleanups = make_cleanup (xfree, section_addrs);

  /* We are done with the temporary bfd.  Get rid of it and make sure
     nobody else can us it.  */
  bfd_close (tmp_bfd);
  tmp_bfd = NULL;

  /* Now let the generic code load up symbols for this library.  */
  section_addrs->other[0].addr = text_addr;
  section_addrs->other[0].name = ".text";
  so->objfile = symbol_file_add (name, from_tty, section_addrs, 0, OBJF_SHARED);
  so->abfd = so->objfile->obfd;

  /* Mark this as a shared library and save private data.  */
  so->objfile->flags |= OBJF_SHARED;

  if (so->objfile->obj_private == NULL)
    {
      obj_private = (obj_private_data_t *)
	obstack_alloc (&so->objfile->objfile_obstack,
		       sizeof (obj_private_data_t));
      obj_private->unwind_info = NULL;
      obj_private->so_info = NULL;
      so->objfile->obj_private = obj_private;
    }

  obj_private = (obj_private_data_t *) so->objfile->obj_private;
  obj_private->so_info = so;
  obj_private->dp = so->pa64_solib_desc.linkage_ptr;
  do_cleanups (my_cleanups);
}