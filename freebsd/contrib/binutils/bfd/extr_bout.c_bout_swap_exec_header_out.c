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
struct internal_exec {int /*<<< orphan*/  a_relaxable; int /*<<< orphan*/  a_balign; int /*<<< orphan*/  a_dalign; int /*<<< orphan*/  a_talign; int /*<<< orphan*/  a_dload; int /*<<< orphan*/  a_tload; int /*<<< orphan*/  a_drsize; int /*<<< orphan*/  a_trsize; int /*<<< orphan*/  a_entry; int /*<<< orphan*/  a_syms; int /*<<< orphan*/  a_bss; int /*<<< orphan*/  a_data; int /*<<< orphan*/  a_text; int /*<<< orphan*/  a_info; } ;
struct external_exec {int /*<<< orphan*/ * e_relaxable; int /*<<< orphan*/ * e_balign; int /*<<< orphan*/ * e_dalign; int /*<<< orphan*/ * e_talign; int /*<<< orphan*/  e_dload; int /*<<< orphan*/  e_tload; int /*<<< orphan*/  e_drsize; int /*<<< orphan*/  e_trsize; int /*<<< orphan*/  e_entry; int /*<<< orphan*/  e_syms; int /*<<< orphan*/  e_bss; int /*<<< orphan*/  e_data; int /*<<< orphan*/  e_text; int /*<<< orphan*/  e_info; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bout_swap_exec_header_out (bfd *abfd,
			   struct internal_exec *execp,
			   struct external_exec *bytes)
{
  /* Now fill in fields in the raw data, from the fields in the exec struct.  */
  H_PUT_32 (abfd, execp->a_info  , bytes->e_info);
  PUT_WORD (abfd, execp->a_text  , bytes->e_text);
  PUT_WORD (abfd, execp->a_data  , bytes->e_data);
  PUT_WORD (abfd, execp->a_bss   , bytes->e_bss);
  PUT_WORD (abfd, execp->a_syms  , bytes->e_syms);
  PUT_WORD (abfd, execp->a_entry , bytes->e_entry);
  PUT_WORD (abfd, execp->a_trsize, bytes->e_trsize);
  PUT_WORD (abfd, execp->a_drsize, bytes->e_drsize);
  PUT_WORD (abfd, execp->a_tload , bytes->e_tload);
  PUT_WORD (abfd, execp->a_dload , bytes->e_dload);
  bytes->e_talign[0]    = execp->a_talign;
  bytes->e_dalign[0]    = execp->a_dalign;
  bytes->e_balign[0]    = execp->a_balign;
  bytes->e_relaxable[0] = execp->a_relaxable;
}