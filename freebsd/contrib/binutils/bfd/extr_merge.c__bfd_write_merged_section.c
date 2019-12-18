#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sec_merge_sec_info {int /*<<< orphan*/ * first_str; } ;
typedef  scalar_t__ file_ptr ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {scalar_t__ output_offset; TYPE_1__* output_section; } ;
typedef  TYPE_2__ asection ;
struct TYPE_4__ {scalar_t__ filepos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_merge_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_write_merged_section (bfd *output_bfd, asection *sec, void *psecinfo)
{
  struct sec_merge_sec_info *secinfo;
  file_ptr pos;

  secinfo = (struct sec_merge_sec_info *) psecinfo;

  if (secinfo->first_str == NULL)
    return TRUE;

  pos = sec->output_section->filepos + sec->output_offset;
  if (bfd_seek (output_bfd, pos, SEEK_SET) != 0)
    return FALSE;

  if (! sec_merge_emit (output_bfd, secinfo->first_str))
    return FALSE;

  return TRUE;
}