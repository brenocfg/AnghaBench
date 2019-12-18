#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* end_epilogue ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* end_function ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* function_epilogue ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 scalar_t__ DWARF2_DEBUG ; 
 scalar_t__ VMS_AND_DWARF2_DEBUG ; 
 int /*<<< orphan*/  app_disable () ; 
 int /*<<< orphan*/  asm_out_file ; 
 TYPE_3__* debug_hooks ; 
 scalar_t__ dwarf2out_do_frame () ; 
 int /*<<< orphan*/  dwarf2out_end_epilogue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_size () ; 
 int /*<<< orphan*/  high_function_linenum ; 
 int /*<<< orphan*/  last_filename ; 
 int /*<<< orphan*/  last_linenum ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 
 scalar_t__ write_symbols ; 

void
final_end_function (void)
{
  app_disable ();

  (*debug_hooks->end_function) (high_function_linenum);

  /* Finally, output the function epilogue:
     code to restore the stack frame and return to the caller.  */
  targetm.asm_out.function_epilogue (asm_out_file, get_frame_size ());

  /* And debug output.  */
  (*debug_hooks->end_epilogue) (last_linenum, last_filename);

#if defined (DWARF2_UNWIND_INFO)
  if (write_symbols != DWARF2_DEBUG && write_symbols != VMS_AND_DWARF2_DEBUG
      && dwarf2out_do_frame ())
    dwarf2out_end_epilogue (last_linenum, last_filename);
#endif
}