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

/* Variables and functions */
 struct frame_info* get_selected_frame () ; 
 int /*<<< orphan*/  target_has_memory ; 
 int /*<<< orphan*/  target_has_registers ; 
 int /*<<< orphan*/  target_has_stack ; 

struct frame_info *
deprecated_safe_get_selected_frame (void)
{
  if (!target_has_registers || !target_has_stack || !target_has_memory)
    return NULL;
  return get_selected_frame ();
}