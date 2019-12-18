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
struct ieee_handle {int block_depth; int /*<<< orphan*/  vars; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ieee_bb_record_enum ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_output_pending_parms (struct ieee_handle*) ; 
 int /*<<< orphan*/  ieee_start_range (struct ieee_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,char*) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
ieee_start_block (void *p, bfd_vma addr)
{
  struct ieee_handle *info = (struct ieee_handle *) p;

  if (! ieee_change_buffer (info, &info->vars))
    return FALSE;

  if (info->block_depth == 1)
    {
      if (! ieee_write_number (info, addr)
	  || ! ieee_output_pending_parms (info))
	return FALSE;
    }
  else
    {
      if (! ieee_write_byte (info, (int) ieee_bb_record_enum)
	  || ! ieee_write_byte (info, 6)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_id (info, "")
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_number (info, addr))
	return FALSE;
    }

  if (! ieee_start_range (info, addr))
    return FALSE;

  ++info->block_depth;

  return TRUE;
}