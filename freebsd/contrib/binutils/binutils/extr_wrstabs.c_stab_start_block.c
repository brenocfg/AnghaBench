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
struct stab_write_handle {int so_offset; int fun_offset; int nesting; scalar_t__ fnaddr; scalar_t__ pending_lbrac; scalar_t__ symbols; int /*<<< orphan*/  abfd; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_LBRAC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const*) ; 

__attribute__((used)) static bfd_boolean
stab_start_block (void *p, bfd_vma addr)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  /* Fill in any slots which have been waiting for the first known
     text address.  */

  if (info->so_offset != -1)
    {
      bfd_put_32 (info->abfd, addr, info->symbols + info->so_offset + 8);
      info->so_offset = -1;
    }

  if (info->fun_offset != -1)
    {
      bfd_put_32 (info->abfd, addr, info->symbols + info->fun_offset + 8);
      info->fun_offset = -1;
    }

  ++info->nesting;

  /* We will be called with a top level block surrounding the
     function, but stabs information does not output that block, so we
     ignore it.  */

  if (info->nesting == 1)
    {
      info->fnaddr = addr;
      return TRUE;
    }

  /* We have to output the LBRAC symbol after any variables which are
     declared inside the block.  We postpone the LBRAC until the next
     start_block or end_block.  */

  /* If we have postponed an LBRAC, output it now.  */
  if (info->pending_lbrac != (bfd_vma) -1)
    {
      if (! stab_write_symbol (info, N_LBRAC, 0, info->pending_lbrac,
			       (const char *) NULL))
	return FALSE;
    }

  /* Remember the address and output it later.  */

  info->pending_lbrac = addr - info->fnaddr;

  return TRUE;
}