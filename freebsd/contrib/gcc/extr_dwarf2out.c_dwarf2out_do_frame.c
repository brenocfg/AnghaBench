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

/* Variables and functions */
 scalar_t__ DWARF2_DEBUG ; 
 scalar_t__ DWARF2_FRAME_INFO ; 
 scalar_t__ DWARF2_UNWIND_INFO ; 
 int /*<<< orphan*/  USING_SJLJ_EXCEPTIONS ; 
 scalar_t__ VMS_AND_DWARF2_DEBUG ; 
 scalar_t__ flag_exceptions ; 
 scalar_t__ flag_unwind_tables ; 
 scalar_t__ write_symbols ; 

int
dwarf2out_do_frame (void)
{
  /* We want to emit correct CFA location expressions or lists, so we
     have to return true if we're going to output debug info, even if
     we're not going to output frame or unwind info.  */
  return (write_symbols == DWARF2_DEBUG
	  || write_symbols == VMS_AND_DWARF2_DEBUG
	  || DWARF2_FRAME_INFO
#ifdef DWARF2_UNWIND_INFO
	  || (DWARF2_UNWIND_INFO
	      && (flag_unwind_tables
		  || (flag_exceptions && ! USING_SJLJ_EXCEPTIONS)))
#endif
	  );
}