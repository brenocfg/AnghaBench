#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stab_info {int /*<<< orphan*/  includes; int /*<<< orphan*/  strings; TYPE_1__* stabstr; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ filepos; } ;
struct TYPE_3__ {scalar_t__ output_offset; TYPE_2__* output_section; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_stringtab_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_stringtab_free (int /*<<< orphan*/ ) ; 
 scalar_t__ _bfd_stringtab_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_abs_section (TYPE_2__*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_write_stab_strings (bfd *output_bfd, struct stab_info *sinfo)
{
  if (bfd_is_abs_section (sinfo->stabstr->output_section))
    /* The section was discarded from the link.  */
    return TRUE;

  BFD_ASSERT ((sinfo->stabstr->output_offset
	       + _bfd_stringtab_size (sinfo->strings))
	      <= sinfo->stabstr->output_section->size);

  if (bfd_seek (output_bfd,
		(file_ptr) (sinfo->stabstr->output_section->filepos
			    + sinfo->stabstr->output_offset),
		SEEK_SET) != 0)
    return FALSE;

  if (! _bfd_stringtab_emit (output_bfd, sinfo->strings))
    return FALSE;

  /* We no longer need the stabs information.  */
  _bfd_stringtab_free (sinfo->strings);
  bfd_hash_table_free (&sinfo->includes);

  return TRUE;
}