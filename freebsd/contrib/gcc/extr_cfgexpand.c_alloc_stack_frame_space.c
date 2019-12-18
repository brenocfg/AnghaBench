#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  decl; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ FRAME_GROWS_DOWNWARD ; 
 TYPE_1__* cfun ; 
 int frame_offset ; 
 scalar_t__ frame_offset_overflow (int,int /*<<< orphan*/ ) ; 
 int frame_phase ; 

__attribute__((used)) static HOST_WIDE_INT
alloc_stack_frame_space (HOST_WIDE_INT size, HOST_WIDE_INT align)
{
  HOST_WIDE_INT offset, new_frame_offset;

  new_frame_offset = frame_offset;
  if (FRAME_GROWS_DOWNWARD)
    {
      new_frame_offset -= size + frame_phase;
      new_frame_offset &= -align;
      new_frame_offset += frame_phase;
      offset = new_frame_offset;
    }
  else
    {
      new_frame_offset -= frame_phase;
      new_frame_offset += align - 1;
      new_frame_offset &= -align;
      new_frame_offset += frame_phase;
      offset = new_frame_offset;
      new_frame_offset += size;
    }
  frame_offset = new_frame_offset;

  if (frame_offset_overflow (frame_offset, cfun->decl))
    frame_offset = offset = 0;

  return offset;
}