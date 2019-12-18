#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* bfd_section; } ;
typedef  TYPE_1__ segment_info_type ;
typedef  void* segT ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_set_section_userdata (int /*<<< orphan*/ ,void*,TYPE_1__*) ; 
 void* now_seg ; 
 int now_subseg ; 
 TYPE_1__* seg_info (void*) ; 
 int /*<<< orphan*/  stdoutput ; 
 TYPE_1__* xcalloc (int,int) ; 

void
subseg_change (register segT seg, register int subseg)
{
  segment_info_type *seginfo = seg_info (seg);
  now_seg = seg;
  now_subseg = subseg;

  if (! seginfo)
    {
      seginfo = xcalloc (1, sizeof (*seginfo));
      seginfo->bfd_section = seg;
      (void) bfd_set_section_userdata (stdoutput, seg, seginfo);
    }
}