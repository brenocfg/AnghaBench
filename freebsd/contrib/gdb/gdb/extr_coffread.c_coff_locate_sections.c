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
struct stab_section_list {struct stab_section_list* next; int /*<<< orphan*/ * section; } ;
struct coff_symfile_info {struct stab_section_list* stabsects; int /*<<< orphan*/ * stabstrsect; int /*<<< orphan*/  textsize; int /*<<< orphan*/  textaddr; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (char const*,char*) ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,struct stab_section_list*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
coff_locate_sections (bfd *abfd, asection *sectp, void *csip)
{
  struct coff_symfile_info *csi;
  const char *name;

  csi = (struct coff_symfile_info *) csip;
  name = bfd_get_section_name (abfd, sectp);
  if (DEPRECATED_STREQ (name, ".text"))
    {
      csi->textaddr = bfd_section_vma (abfd, sectp);
      csi->textsize += bfd_section_size (abfd, sectp);
    }
  else if (strncmp (name, ".text", sizeof ".text" - 1) == 0)
    {
      csi->textsize += bfd_section_size (abfd, sectp);
    }
  else if (DEPRECATED_STREQ (name, ".stabstr"))
    {
      csi->stabstrsect = sectp;
    }
  else if (strncmp (name, ".stab", sizeof ".stab" - 1) == 0)
    {
      const char *s;

      /* We can have multiple .stab sections if linked with
         --split-by-reloc.  */
      for (s = name + sizeof ".stab" - 1; *s != '\0'; s++)
	if (!isdigit (*s))
	  break;
      if (*s == '\0')
	{
	  struct stab_section_list *n, **pn;

	  n = ((struct stab_section_list *)
	       xmalloc (sizeof (struct stab_section_list)));
	  n->section = sectp;
	  n->next = NULL;
	  for (pn = &csi->stabsects; *pn != NULL; pn = &(*pn)->next)
	    ;
	  *pn = n;

	  /* This will be run after coffstab_build_psymtabs is called
	     in coff_symfile_read, at which point we no longer need
	     the information.  */
	  make_cleanup (xfree, n);
	}
    }
}