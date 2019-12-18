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
 int /*<<< orphan*/  get_frame_base (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 

__attribute__((used)) static CORE_ADDR
default_frame_base_address (struct frame_info *next_frame, void **this_cache)
{
  struct frame_info *this_frame = get_prev_frame (next_frame);
  return get_frame_base (this_frame); /* sigh! */
}