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
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;

/* Variables and functions */
 struct frame_id null_frame_id ; 

__attribute__((used)) static void
legacy_saved_regs_this_id (struct frame_info *next_frame,
			   void **this_prologue_cache,
			   struct frame_id *id)
{
  /* A developer is trying to bring up a new architecture, help them
     by providing a default unwinder that refuses to unwind anything
     (the ID is always NULL).  In the case of legacy code,
     legacy_get_prev_frame() will have previously set ->this_id.p, so
     this code won't be called.  */
  (*id) = null_frame_id;
}