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
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/ ** linescreen; } ;

/* Variables and functions */
 TYPE_1__ tt_context ; 

void TitanPutLineHLine(int linescreen, s32 y, u32 color)
{
   if (linescreen == 0) return;

   {
      u32 * buffer = tt_context.linescreen[linescreen] + y;
      *buffer = color;
   }
}