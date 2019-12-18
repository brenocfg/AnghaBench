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
struct arm_prologue_cache {scalar_t__ prev_sp; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ LOWEST_PC ; 
 scalar_t__ NORMAL_FRAME ; 
 void* arm_make_prologue_cache (struct frame_info*) ; 
 scalar_t__ frame_func_unwind (struct frame_info*) ; 
 struct frame_id frame_id_build (scalar_t__,scalar_t__) ; 
 scalar_t__ frame_id_eq (int /*<<< orphan*/ ,struct frame_id) ; 
 scalar_t__ frame_relative_level (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_id (struct frame_info*) ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 

__attribute__((used)) static void
arm_prologue_this_id (struct frame_info *next_frame,
		      void **this_cache,
		      struct frame_id *this_id)
{
  struct arm_prologue_cache *cache;
  struct frame_id id;
  CORE_ADDR func;

  if (*this_cache == NULL)
    *this_cache = arm_make_prologue_cache (next_frame);
  cache = *this_cache;

  func = frame_func_unwind (next_frame);

  /* This is meant to halt the backtrace at "_start".  Make sure we
     don't halt it at a generic dummy frame. */
  if (func <= LOWEST_PC)
    return;

  /* If we've hit a wall, stop.  */
  if (cache->prev_sp == 0)
    return;

  id = frame_id_build (cache->prev_sp, func);

  /* Check that we're not going round in circles with the same frame
     ID (but avoid applying the test to sentinel frames which do go
     round in circles).  */
  if (frame_relative_level (next_frame) >= 0
      && get_frame_type (next_frame) == NORMAL_FRAME
      && frame_id_eq (get_frame_id (next_frame), id))
    return;

  *this_id = id;
}