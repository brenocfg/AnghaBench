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
struct stab_section_info {struct stab_section_info* next; } ;
struct objfile {int /*<<< orphan*/  md; struct dbx_symfile_info* sym_stab_info; } ;
struct dbx_symfile_info {struct stab_section_info* stab_section_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,struct stab_section_info*) ; 

__attribute__((used)) static void
free_elfinfo (void *objp)
{
  struct objfile *objfile = (struct objfile *) objp;
  struct dbx_symfile_info *dbxinfo = objfile->sym_stab_info;
  struct stab_section_info *ssi, *nssi;

  ssi = dbxinfo->stab_section_info;
  while (ssi)
    {
      nssi = ssi->next;
      xmfree (objfile->md, ssi);
      ssi = nssi;
    }

  dbxinfo->stab_section_info = 0;	/* Just say No mo info about this.  */
}