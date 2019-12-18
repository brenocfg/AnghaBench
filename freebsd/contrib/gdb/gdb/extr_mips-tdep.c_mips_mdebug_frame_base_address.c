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
struct mips_frame_cache {int /*<<< orphan*/  base; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct mips_frame_cache* mips_mdebug_frame_cache (struct frame_info*,void**) ; 

__attribute__((used)) static CORE_ADDR
mips_mdebug_frame_base_address (struct frame_info *next_frame,
				void **this_cache)
{
  struct mips_frame_cache *info = mips_mdebug_frame_cache (next_frame,
							   this_cache);
  return info->base;
}