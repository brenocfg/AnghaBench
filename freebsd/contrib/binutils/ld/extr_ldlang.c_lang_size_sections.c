#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {unsigned int vma; unsigned int alignment_power; struct TYPE_7__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_6__ {scalar_t__ phase; int relro_end; unsigned int min_base; unsigned int maxpagesize; int base; int pagesize; int end; } ;
struct TYPE_10__ {int /*<<< orphan*/  phase; TYPE_1__ dataseg; } ;
struct TYPE_9__ {int relro_start; unsigned int relro_end; scalar_t__ relro; } ;
struct TYPE_8__ {TYPE_2__* sections; } ;

/* Variables and functions */
 scalar_t__ exp_dataseg_adjust ; 
 scalar_t__ exp_dataseg_end_seen ; 
 scalar_t__ exp_dataseg_none ; 
 scalar_t__ exp_dataseg_relro_adjust ; 
 TYPE_5__ expld ; 
 int /*<<< orphan*/  lang_allocating_phase_enum ; 
 int /*<<< orphan*/  lang_final_phase_enum ; 
 int /*<<< orphan*/  lang_reset_memory_regions () ; 
 TYPE_4__ link_info ; 
 int /*<<< orphan*/  one_lang_size_sections_pass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* output_bfd ; 

void
lang_size_sections (bfd_boolean *relax, bfd_boolean check_regions)
{
  expld.phase = lang_allocating_phase_enum;
  expld.dataseg.phase = exp_dataseg_none;

  one_lang_size_sections_pass (relax, check_regions);
  if (expld.dataseg.phase == exp_dataseg_end_seen
      && link_info.relro && expld.dataseg.relro_end)
    {
      /* If DATA_SEGMENT_ALIGN DATA_SEGMENT_RELRO_END pair was seen, try
	 to put expld.dataseg.relro on a (common) page boundary.  */
      bfd_vma old_min_base, relro_end, maxpage;

      expld.dataseg.phase = exp_dataseg_relro_adjust;
      old_min_base = expld.dataseg.min_base;
      maxpage = expld.dataseg.maxpagesize;
      expld.dataseg.base += (-expld.dataseg.relro_end
			     & (expld.dataseg.pagesize - 1));
      /* Compute the expected PT_GNU_RELRO segment end.  */
      relro_end = (expld.dataseg.relro_end + expld.dataseg.pagesize - 1)
		  & ~(expld.dataseg.pagesize - 1);
      if (old_min_base + maxpage < expld.dataseg.base)
	{
	  expld.dataseg.base -= maxpage;
	  relro_end -= maxpage;
	}
      lang_reset_memory_regions ();
      one_lang_size_sections_pass (relax, check_regions);
      if (expld.dataseg.relro_end > relro_end)
	{
	  /* The alignment of sections between DATA_SEGMENT_ALIGN
	     and DATA_SEGMENT_RELRO_END caused huge padding to be
	     inserted at DATA_SEGMENT_RELRO_END.  Try some other base.  */
	  asection *sec;
	  unsigned int max_alignment_power = 0;

	  /* Find maximum alignment power of sections between
	     DATA_SEGMENT_ALIGN and DATA_SEGMENT_RELRO_END.  */
	  for (sec = output_bfd->sections; sec; sec = sec->next)
	    if (sec->vma >= expld.dataseg.base
		&& sec->vma < expld.dataseg.relro_end
		&& sec->alignment_power > max_alignment_power)
	      max_alignment_power = sec->alignment_power;

	  if (((bfd_vma) 1 << max_alignment_power) < expld.dataseg.pagesize)
	    {
	      if (expld.dataseg.base - (1 << max_alignment_power)
		  < old_min_base)
		expld.dataseg.base += expld.dataseg.pagesize;
	      expld.dataseg.base -= (1 << max_alignment_power);
	      lang_reset_memory_regions ();
	      one_lang_size_sections_pass (relax, check_regions);
	    }
	}
      link_info.relro_start = expld.dataseg.base;
      link_info.relro_end = expld.dataseg.relro_end;
    }
  else if (expld.dataseg.phase == exp_dataseg_end_seen)
    {
      /* If DATA_SEGMENT_ALIGN DATA_SEGMENT_END pair was seen, check whether
	 a page could be saved in the data segment.  */
      bfd_vma first, last;

      first = -expld.dataseg.base & (expld.dataseg.pagesize - 1);
      last = expld.dataseg.end & (expld.dataseg.pagesize - 1);
      if (first && last
	  && ((expld.dataseg.base & ~(expld.dataseg.pagesize - 1))
	      != (expld.dataseg.end & ~(expld.dataseg.pagesize - 1)))
	  && first + last <= expld.dataseg.pagesize)
	{
	  expld.dataseg.phase = exp_dataseg_adjust;
	  lang_reset_memory_regions ();
	  one_lang_size_sections_pass (relax, check_regions);
	}
    }

  expld.phase = lang_final_phase_enum;
}