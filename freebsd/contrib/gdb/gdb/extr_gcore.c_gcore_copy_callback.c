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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int SEC_LOAD ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  paddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_d (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xfree ; 
 void* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gcore_copy_callback (bfd *obfd, asection *osec, void *ignored)
{
  bfd_size_type size = bfd_section_size (obfd, osec);
  struct cleanup *old_chain = NULL;
  void *memhunk;

  /* Read-only sections are marked; we don't have to copy their contents.  */
  if ((bfd_get_section_flags (obfd, osec) & SEC_LOAD) == 0)
    return;

  /* Only interested in "load" sections.  */
  if (strncmp ("load", bfd_section_name (obfd, osec), 4) != 0)
    return;

  memhunk = xmalloc (size);
  /* ??? This is crap since xmalloc should never return NULL.  */
  if (memhunk == NULL)
    error ("Not enough memory to create corefile.");
  old_chain = make_cleanup (xfree, memhunk);

  if (target_read_memory (bfd_section_vma (obfd, osec),
			  memhunk, size) != 0)
    warning ("Memory read failed for corefile section, %s bytes at 0x%s\n",
	     paddr_d (size), paddr (bfd_section_vma (obfd, osec)));
  if (!bfd_set_section_contents (obfd, osec, memhunk, 0, size))
    warning ("Failed to write corefile contents (%s).",
	     bfd_errmsg (bfd_get_error ()));

  do_cleanups (old_chain);	/* Frees MEMHUNK.  */
}