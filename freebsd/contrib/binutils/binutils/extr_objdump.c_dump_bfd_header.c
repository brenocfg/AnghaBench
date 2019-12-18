#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  start_address; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_IS_RELAXABLE ; 
 int /*<<< orphan*/  DYNAMIC ; 
 int /*<<< orphan*/  D_PAGED ; 
 int /*<<< orphan*/  EXEC_P ; 
 int /*<<< orphan*/  HAS_DEBUG ; 
 int /*<<< orphan*/  HAS_LINENO ; 
 int /*<<< orphan*/  HAS_LOAD_PAGE ; 
 int /*<<< orphan*/  HAS_LOCALS ; 
 int /*<<< orphan*/  HAS_RELOC ; 
 int /*<<< orphan*/  HAS_SYMS ; 
 int /*<<< orphan*/  PF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WP_TEXT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_get_arch (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_get_mach (TYPE_1__*) ; 
 char* bfd_printable_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_printf_vma (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_bfd_header (bfd *abfd)
{
  char *comma = "";

  printf (_("architecture: %s, "),
	  bfd_printable_arch_mach (bfd_get_arch (abfd),
				   bfd_get_mach (abfd)));
  printf (_("flags 0x%08x:\n"), abfd->flags);

#define PF(x, y)    if (abfd->flags & x) {printf("%s%s", comma, y); comma=", ";}
  PF (HAS_RELOC, "HAS_RELOC");
  PF (EXEC_P, "EXEC_P");
  PF (HAS_LINENO, "HAS_LINENO");
  PF (HAS_DEBUG, "HAS_DEBUG");
  PF (HAS_SYMS, "HAS_SYMS");
  PF (HAS_LOCALS, "HAS_LOCALS");
  PF (DYNAMIC, "DYNAMIC");
  PF (WP_TEXT, "WP_TEXT");
  PF (D_PAGED, "D_PAGED");
  PF (BFD_IS_RELAXABLE, "BFD_IS_RELAXABLE");
  PF (HAS_LOAD_PAGE, "HAS_LOAD_PAGE");
  printf (_("\nstart address 0x"));
  bfd_printf_vma (abfd, abfd->start_address);
  printf ("\n");
}