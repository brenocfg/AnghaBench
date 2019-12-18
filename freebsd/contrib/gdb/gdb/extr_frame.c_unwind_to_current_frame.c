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
struct ui_out {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 struct frame_info* current_frame ; 
 struct frame_info* get_prev_frame (void*) ; 

__attribute__((used)) static int
unwind_to_current_frame (struct ui_out *ui_out, void *args)
{
  struct frame_info *frame = get_prev_frame (args);
  /* A sentinel frame can fail to unwind, eg, because it's PC value
     lands in somewhere like start.  */
  if (frame == NULL)
    return 1;
  current_frame = frame;
  return 0;
}