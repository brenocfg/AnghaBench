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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_FRAME_LOCALS_ADDRESS (struct frame_info*) ; 
 scalar_t__ DEPRECATED_FRAME_LOCALS_ADDRESS_P () ; 
 int /*<<< orphan*/  default_frame_base_address (struct frame_info*,void**) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 

__attribute__((used)) static CORE_ADDR
default_frame_locals_address (struct frame_info *next_frame, void **this_cache)
{
  if (DEPRECATED_FRAME_LOCALS_ADDRESS_P ())
    {
      /* This is bad.  The computation of per-frame locals address
	 should use a per-frame frame-base.  */
      struct frame_info *this_frame = get_prev_frame (next_frame);
      return DEPRECATED_FRAME_LOCALS_ADDRESS (this_frame);
    }
  return default_frame_base_address (next_frame, this_cache);
}