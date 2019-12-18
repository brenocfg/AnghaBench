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
struct block {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BLOCK_END (struct block*) ; 
 scalar_t__ BLOCK_START (struct block*) ; 
 scalar_t__ get_frame_address_in_block (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 

struct frame_info *
block_innermost_frame (struct block *block)
{
  struct frame_info *frame;
  CORE_ADDR start;
  CORE_ADDR end;
  CORE_ADDR calling_pc;

  if (block == NULL)
    return NULL;

  start = BLOCK_START (block);
  end = BLOCK_END (block);

  frame = NULL;
  while (1)
    {
      frame = get_prev_frame (frame);
      if (frame == NULL)
	return NULL;
      calling_pc = get_frame_address_in_block (frame);
      if (calling_pc >= start && calling_pc < end)
	return frame;
    }
}