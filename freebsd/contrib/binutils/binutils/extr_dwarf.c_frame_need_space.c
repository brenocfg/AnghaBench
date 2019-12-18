#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ncols; scalar_t__* col_offset; scalar_t__* col_type; } ;
typedef  TYPE_1__ Frame_Chunk ;

/* Variables and functions */
 scalar_t__ DW_CFA_unreferenced ; 
 void* xcrealloc (scalar_t__*,int,int) ; 

__attribute__((used)) static void
frame_need_space (Frame_Chunk *fc, int reg)
{
  int prev = fc->ncols;

  if (reg < fc->ncols)
    return;

  fc->ncols = reg + 1;
  fc->col_type = xcrealloc (fc->col_type, fc->ncols, sizeof (short int));
  fc->col_offset = xcrealloc (fc->col_offset, fc->ncols, sizeof (int));

  while (prev < fc->ncols)
    {
      fc->col_type[prev] = DW_CFA_unreferenced;
      fc->col_offset[prev] = 0;
      prev++;
    }
}