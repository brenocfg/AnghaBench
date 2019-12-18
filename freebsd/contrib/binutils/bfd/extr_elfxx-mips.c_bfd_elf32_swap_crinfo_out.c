#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/  vaddr; int /*<<< orphan*/  konst; int /*<<< orphan*/  info; } ;
struct TYPE_5__ {unsigned long ctype; unsigned long rtype; unsigned long dist2to; unsigned long relvaddr; unsigned long konst; unsigned long vaddr; } ;
typedef  TYPE_1__ Elf32_crinfo ;
typedef  TYPE_2__ Elf32_External_crinfo ;

/* Variables and functions */
 unsigned long CRINFO_CTYPE ; 
 unsigned long CRINFO_CTYPE_SH ; 
 unsigned long CRINFO_DIST2TO ; 
 unsigned long CRINFO_DIST2TO_SH ; 
 unsigned long CRINFO_RELVADDR ; 
 unsigned long CRINFO_RELVADDR_SH ; 
 unsigned long CRINFO_RTYPE ; 
 unsigned long CRINFO_RTYPE_SH ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfd_elf32_swap_crinfo_out (bfd *abfd, const Elf32_crinfo *in,
			   Elf32_External_crinfo *ex)
{
  unsigned long l;

  l = (((in->ctype & CRINFO_CTYPE) << CRINFO_CTYPE_SH)
       | ((in->rtype & CRINFO_RTYPE) << CRINFO_RTYPE_SH)
       | ((in->dist2to & CRINFO_DIST2TO) << CRINFO_DIST2TO_SH)
       | ((in->relvaddr & CRINFO_RELVADDR) << CRINFO_RELVADDR_SH));
  H_PUT_32 (abfd, l, ex->info);
  H_PUT_32 (abfd, in->konst, ex->konst);
  H_PUT_32 (abfd, in->vaddr, ex->vaddr);
}