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
struct frame_info {scalar_t__ unwind; void* prologue_cache; void* base_cache; int /*<<< orphan*/  next; TYPE_1__* base; } ;
struct TYPE_2__ {scalar_t__ unwind; int /*<<< orphan*/  (* this_locals ) (int /*<<< orphan*/ ,void**) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ NORMAL_FRAME ; 
 TYPE_1__* frame_base_find_by_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void**) ; 

CORE_ADDR
get_frame_locals_address (struct frame_info *fi)
{
  void **cache;
  if (get_frame_type (fi) != NORMAL_FRAME)
    return 0;
  /* If there isn't a frame address method, find it.  */
  if (fi->base == NULL)
    fi->base = frame_base_find_by_frame (fi->next);
  /* Sneaky: If the low-level unwind and high-level base code share a
     common unwinder, let them share the prologue cache.  */
  if (fi->base->unwind == fi->unwind)
    cache = &fi->prologue_cache;
  else
    cache = &fi->base_cache;
  return fi->base->this_locals (fi->next, cache);
}