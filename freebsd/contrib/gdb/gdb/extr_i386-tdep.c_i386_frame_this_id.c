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
struct i386_frame_cache {scalar_t__ base; int /*<<< orphan*/  pc; } ;
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;

/* Variables and functions */
 struct frame_id frame_id_build (scalar_t__,int /*<<< orphan*/ ) ; 
 struct i386_frame_cache* i386_frame_cache (struct frame_info*,void**) ; 

__attribute__((used)) static void
i386_frame_this_id (struct frame_info *next_frame, void **this_cache,
		    struct frame_id *this_id)
{
  struct i386_frame_cache *cache = i386_frame_cache (next_frame, this_cache);

  /* This marks the outermost frame.  */
  if (cache->base == 0)
    return;

  /* See the end of i386_push_dummy_call.  */
  (*this_id) = frame_id_build (cache->base + 8, cache->pc);
}