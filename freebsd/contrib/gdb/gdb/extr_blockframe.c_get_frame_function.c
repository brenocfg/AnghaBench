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
struct symbol {int dummy; } ;
struct frame_info {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 struct symbol* block_function (struct block*) ; 
 struct block* get_frame_block (struct frame_info*,int /*<<< orphan*/ ) ; 

struct symbol *
get_frame_function (struct frame_info *frame)
{
  struct block *bl = get_frame_block (frame, 0);
  if (bl == 0)
    return 0;
  return block_function (bl);
}