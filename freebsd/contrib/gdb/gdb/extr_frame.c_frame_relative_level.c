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
struct frame_info {int level; } ;

/* Variables and functions */

int
frame_relative_level (struct frame_info *fi)
{
  if (fi == NULL)
    return -1;
  else
    return fi->level;
}