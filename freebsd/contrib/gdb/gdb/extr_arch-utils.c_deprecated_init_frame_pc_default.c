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
 int /*<<< orphan*/  DEPRECATED_FRAME_SAVED_PC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEPRECATED_SAVED_PC_AFTER_CALL (int /*<<< orphan*/ *) ; 
 scalar_t__ DEPRECATED_SAVED_PC_AFTER_CALL_P () ; 
 int /*<<< orphan*/ * get_next_frame (struct frame_info*) ; 
 int /*<<< orphan*/  read_pc () ; 

CORE_ADDR
deprecated_init_frame_pc_default (int fromleaf, struct frame_info *prev)
{
  if (fromleaf && DEPRECATED_SAVED_PC_AFTER_CALL_P ())
    return DEPRECATED_SAVED_PC_AFTER_CALL (get_next_frame (prev));
  else if (get_next_frame (prev) != NULL)
    return DEPRECATED_FRAME_SAVED_PC (get_next_frame (prev));
  else
    return read_pc ();
}