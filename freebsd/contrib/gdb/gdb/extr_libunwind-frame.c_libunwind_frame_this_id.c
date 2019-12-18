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
struct libunwind_frame_cache {int /*<<< orphan*/  func_addr; int /*<<< orphan*/  base; } ;
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;

/* Variables and functions */
 struct frame_id frame_id_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct libunwind_frame_cache* libunwind_frame_cache (struct frame_info*,void**) ; 

void
libunwind_frame_this_id (struct frame_info *next_frame, void **this_cache,
		      struct frame_id *this_id)
{
  struct libunwind_frame_cache *cache =
    libunwind_frame_cache (next_frame, this_cache);

  (*this_id) = frame_id_build (cache->base, cache->func_addr);
}