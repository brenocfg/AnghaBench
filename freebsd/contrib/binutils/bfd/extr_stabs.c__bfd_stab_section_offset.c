#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stab_section_info {size_t* cumulative_skips; scalar_t__* stridxs; } ;
typedef  size_t bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_3__ {size_t rawsize; size_t size; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 size_t STABSIZE ; 

bfd_vma
_bfd_stab_section_offset (asection *stabsec,
			  void * psecinfo,
			  bfd_vma offset)
{
  struct stab_section_info *secinfo;

  secinfo = (struct stab_section_info *) psecinfo;

  if (secinfo == NULL)
    return offset;

  if (offset >= stabsec->rawsize)
    return offset - stabsec->rawsize + stabsec->size;

  if (secinfo->cumulative_skips)
    {
      bfd_vma i;

      i = offset / STABSIZE;

      if (secinfo->stridxs [i] == (bfd_size_type) -1)
	return (bfd_vma) -1;

      return offset - secinfo->cumulative_skips [i];
    }

  return offset;
}