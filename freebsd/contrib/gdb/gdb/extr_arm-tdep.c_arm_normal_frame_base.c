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
struct arm_prologue_cache {scalar_t__ framesize; scalar_t__ frameoffset; scalar_t__ prev_sp; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 void* arm_make_prologue_cache (struct frame_info*) ; 

__attribute__((used)) static CORE_ADDR
arm_normal_frame_base (struct frame_info *next_frame, void **this_cache)
{
  struct arm_prologue_cache *cache;

  if (*this_cache == NULL)
    *this_cache = arm_make_prologue_cache (next_frame);
  cache = *this_cache;

  return cache->prev_sp + cache->frameoffset - cache->framesize;
}