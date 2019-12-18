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
struct function {int /*<<< orphan*/  x_frame_offset; } ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ FRAME_GROWS_DOWNWARD ; 

__attribute__((used)) static HOST_WIDE_INT
get_func_frame_size (struct function *f)
{
  if (FRAME_GROWS_DOWNWARD)
    return -f->x_frame_offset;
  else
    return f->x_frame_offset;
}