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
struct alpha_mdebug_unwind_cache {int /*<<< orphan*/  vfp; } ;

/* Variables and functions */
 struct alpha_mdebug_unwind_cache* alpha_mdebug_frame_unwind_cache (struct frame_info*,void**) ; 
 int /*<<< orphan*/  frame_func_unwind (struct frame_info*) ; 
 struct frame_id frame_id_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
alpha_mdebug_frame_this_id (struct frame_info *next_frame,
			    void **this_prologue_cache,
			    struct frame_id *this_id)
{
  struct alpha_mdebug_unwind_cache *info
    = alpha_mdebug_frame_unwind_cache (next_frame, this_prologue_cache);

  *this_id = frame_id_build (info->vfp, frame_func_unwind (next_frame));
}