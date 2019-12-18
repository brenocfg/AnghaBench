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
struct stab_write_handle {scalar_t__ last_text_address; scalar_t__ pending_lbrac; scalar_t__ nesting; scalar_t__ fnaddr; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_LBRAC ; 
 int /*<<< orphan*/  N_RBRAC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char const*) ; 

__attribute__((used)) static bfd_boolean
stab_end_block (void *p, bfd_vma addr)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  if (addr > info->last_text_address)
    info->last_text_address = addr;

  /* If we have postponed an LBRAC, output it now.  */
  if (info->pending_lbrac != (bfd_vma) -1)
    {
      if (! stab_write_symbol (info, N_LBRAC, 0, info->pending_lbrac,
			       (const char *) NULL))
	return FALSE;
      info->pending_lbrac = (bfd_vma) -1;
    }

  assert (info->nesting > 0);

  --info->nesting;

  /* We ignore the outermost block.  */
  if (info->nesting == 0)
    return TRUE;

  return stab_write_symbol (info, N_RBRAC, 0, addr - info->fnaddr,
			    (const char *) NULL);
}