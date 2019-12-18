#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {scalar_t__ entsize; } ;
typedef  TYPE_1__ asection ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 TYPE_1__* bfd_make_section_anyway (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bfd_openw_with_cleanup (char*,char*,char*) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfd_set_section_vma (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_bfd_file (char *filename, char *mode, 
	       char *target, CORE_ADDR vaddr, 
	       char *buf, int len)
{
  bfd *obfd;
  asection *osection;

  obfd = bfd_openw_with_cleanup (filename, target, mode);
  osection = bfd_make_section_anyway (obfd, ".newsec");
  bfd_set_section_size (obfd, osection, len);
  bfd_set_section_vma (obfd, osection, vaddr);
  bfd_set_section_alignment (obfd, osection, 0);
  bfd_set_section_flags (obfd, osection, 0x203);
  osection->entsize = 0;
  bfd_set_section_contents (obfd, osection, buf, 0, len);
}