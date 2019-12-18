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
struct frame_info {int type; } ;
typedef  enum frame_type { ____Placeholder_frame_type } frame_type ;

/* Variables and functions */

void
deprecated_set_frame_type (struct frame_info *frame, enum frame_type type)
{
  /* Arrrg!  See comment in "frame.h".  */
  frame->type = type;
}