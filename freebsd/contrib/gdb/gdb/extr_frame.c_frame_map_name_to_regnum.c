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
 int /*<<< orphan*/  get_frame_arch (struct frame_info*) ; 
 int user_reg_map_name_to_regnum (int /*<<< orphan*/ ,char const*,int) ; 

int
frame_map_name_to_regnum (struct frame_info *frame, const char *name, int len)
{
  return user_reg_map_name_to_regnum (get_frame_arch (frame), name, len);
}