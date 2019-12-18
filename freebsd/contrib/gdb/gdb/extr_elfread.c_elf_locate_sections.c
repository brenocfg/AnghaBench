#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elfinfo {TYPE_1__* mdebugsect; TYPE_1__* stabindexsect; TYPE_1__* stabsect; void* lnsize; int /*<<< orphan*/  lnoffset; void* dbsize; int /*<<< orphan*/  dboffset; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 void* bfd_get_section_size (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
elf_locate_sections (bfd *ignore_abfd, asection *sectp, void *eip)
{
  struct elfinfo *ei;

  ei = (struct elfinfo *) eip;
  if (strcmp (sectp->name, ".debug") == 0)
    {
      ei->dboffset = sectp->filepos;
      ei->dbsize = bfd_get_section_size (sectp);
    }
  else if (strcmp (sectp->name, ".line") == 0)
    {
      ei->lnoffset = sectp->filepos;
      ei->lnsize = bfd_get_section_size (sectp);
    }
  else if (strcmp (sectp->name, ".stab") == 0)
    {
      ei->stabsect = sectp;
    }
  else if (strcmp (sectp->name, ".stab.index") == 0)
    {
      ei->stabindexsect = sectp;
    }
  else if (strcmp (sectp->name, ".mdebug") == 0)
    {
      ei->mdebugsect = sectp;
    }
}