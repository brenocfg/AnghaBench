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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct block* block_for_pc (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  get_frame_address_in_block (struct frame_info*) ; 

struct block *
get_frame_block (struct frame_info *frame, CORE_ADDR *addr_in_block)
{
  const CORE_ADDR pc = get_frame_address_in_block (frame);

  if (addr_in_block)
    *addr_in_block = pc;

  return block_for_pc (pc);
}