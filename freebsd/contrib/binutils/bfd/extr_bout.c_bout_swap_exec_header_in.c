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
struct internal_exec {int /*<<< orphan*/  a_relaxable; int /*<<< orphan*/  a_balign; int /*<<< orphan*/  a_dalign; int /*<<< orphan*/  a_talign; void* a_dload; void* a_tload; void* a_drsize; void* a_trsize; void* a_entry; void* a_syms; void* a_bss; void* a_data; void* a_text; int /*<<< orphan*/  a_info; } ;
struct external_exec {int /*<<< orphan*/ * e_relaxable; int /*<<< orphan*/ * e_balign; int /*<<< orphan*/ * e_dalign; int /*<<< orphan*/ * e_talign; int /*<<< orphan*/  e_dload; int /*<<< orphan*/  e_tload; int /*<<< orphan*/  e_drsize; int /*<<< orphan*/  e_trsize; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_syms; int /*<<< orphan*/  e_bss; int /*<<< orphan*/  e_data; int /*<<< orphan*/  e_text; int /*<<< orphan*/  e_info; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 void* GET_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bout_swap_exec_header_in (bfd *abfd,
			  struct external_exec *bytes,
			  struct internal_exec *execp)
{
  /* Now fill in fields in the execp, from the bytes in the raw data.  */
  execp->a_info      = H_GET_32 (abfd, bytes->e_info);
  execp->a_text      = GET_WORD (abfd, bytes->e_text);
  execp->a_data      = GET_WORD (abfd, bytes->e_data);
  execp->a_bss       = GET_WORD (abfd, bytes->e_bss);
  execp->a_syms      = GET_WORD (abfd, bytes->e_syms);
  execp->a_entry     = GET_WORD (abfd, bytes->e_entry);
  execp->a_trsize    = GET_WORD (abfd, bytes->e_trsize);
  execp->a_drsize    = GET_WORD (abfd, bytes->e_drsize);
  execp->a_tload     = GET_WORD (abfd, bytes->e_tload);
  execp->a_dload     = GET_WORD (abfd, bytes->e_dload);
  execp->a_talign    = bytes->e_talign[0];
  execp->a_dalign    = bytes->e_dalign[0];
  execp->a_balign    = bytes->e_balign[0];
  execp->a_relaxable = bytes->e_relaxable[0];
}