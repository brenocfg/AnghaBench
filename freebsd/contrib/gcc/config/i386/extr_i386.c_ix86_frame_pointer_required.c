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
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ accesses_prev_frame; } ;

/* Variables and functions */
 scalar_t__ SUBTARGET_FRAME_POINTER_REQUIRED ; 
 scalar_t__ TARGET_OMIT_LEAF_FRAME_POINTER ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  current_function_is_leaf ; 
 scalar_t__ current_function_profile ; 
 scalar_t__ ix86_current_function_calls_tls_descriptor ; 

int
ix86_frame_pointer_required (void)
{
  /* If we accessed previous frames, then the generated code expects
     to be able to access the saved ebp value in our frame.  */
  if (cfun->machine->accesses_prev_frame)
    return 1;

  /* Several x86 os'es need a frame pointer for other reasons,
     usually pertaining to setjmp.  */
  if (SUBTARGET_FRAME_POINTER_REQUIRED)
    return 1;

  /* In override_options, TARGET_OMIT_LEAF_FRAME_POINTER turns off
     the frame pointer by default.  Turn it back on now if we've not
     got a leaf function.  */
  if (TARGET_OMIT_LEAF_FRAME_POINTER
      && (!current_function_is_leaf
	  || ix86_current_function_calls_tls_descriptor))
    return 1;

  if (current_function_profile)
    return 1;

  return 0;
}