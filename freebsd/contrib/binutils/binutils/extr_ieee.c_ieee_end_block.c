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
struct ieee_handle {scalar_t__ highaddr; int /*<<< orphan*/  block_depth; int /*<<< orphan*/  vars; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ieee_be_record_enum ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_end_range (struct ieee_handle*,scalar_t__) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
ieee_end_block (void *p, bfd_vma addr)
{
  struct ieee_handle *info = (struct ieee_handle *) p;

  /* The address we are given is the end of the block, but IEEE seems
     to want to the address of the last byte in the block, so we
     subtract one.  */
  if (! ieee_change_buffer (info, &info->vars)
      || ! ieee_write_byte (info, (int) ieee_be_record_enum)
      || ! ieee_write_number (info, addr - 1))
    return FALSE;

  if (! ieee_end_range (info, addr))
    return FALSE;

  --info->block_depth;

  if (addr > info->highaddr)
    info->highaddr = addr;

  return TRUE;
}