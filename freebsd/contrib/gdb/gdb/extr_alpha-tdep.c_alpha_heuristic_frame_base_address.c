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
struct alpha_heuristic_unwind_cache {int /*<<< orphan*/  vfp; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct alpha_heuristic_unwind_cache* alpha_heuristic_frame_unwind_cache (struct frame_info*,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
alpha_heuristic_frame_base_address (struct frame_info *next_frame,
				    void **this_prologue_cache)
{
  struct alpha_heuristic_unwind_cache *info
    = alpha_heuristic_frame_unwind_cache (next_frame, this_prologue_cache, 0);

  return info->vfp;
}