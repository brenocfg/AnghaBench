#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ppc_elf_link_hash_table {scalar_t__ plt_type; unsigned int got_gap; unsigned int got_header_size; TYPE_1__* got; } ;
typedef  unsigned int bfd_vma ;
struct TYPE_2__ {unsigned int size; } ;

/* Variables and functions */
 scalar_t__ PLT_NEW ; 
 scalar_t__ PLT_VXWORKS ; 

__attribute__((used)) static bfd_vma
allocate_got (struct ppc_elf_link_hash_table *htab, unsigned int need)
{
  bfd_vma where;
  unsigned int max_before_header;

  if (htab->plt_type == PLT_VXWORKS)
    {
      where = htab->got->size;
      htab->got->size += need;
    }
  else
    {
      max_before_header = htab->plt_type == PLT_NEW ? 32768 : 32764;
      if (need <= htab->got_gap)
	{
	  where = max_before_header - htab->got_gap;
	  htab->got_gap -= need;
	}
      else
	{
	  if (htab->got->size + need > max_before_header
	      && htab->got->size <= max_before_header)
	    {
	      htab->got_gap = max_before_header - htab->got->size;
	      htab->got->size = max_before_header + htab->got_header_size;
	    }
	  where = htab->got->size;
	  htab->got->size += need;
	}
    }
  return where;
}