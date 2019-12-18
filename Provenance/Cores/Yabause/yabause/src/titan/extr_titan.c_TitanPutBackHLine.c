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
struct PixelData {int /*<<< orphan*/  pixel; } ;
typedef  size_t s32 ;
struct TYPE_2__ {size_t vdp2width; struct PixelData* backscreen; } ;

/* Variables and functions */
 TYPE_1__ tt_context ; 

void TitanPutBackHLine(s32 y, u32 color)
{
   struct PixelData* buffer = &tt_context.backscreen[(y * tt_context.vdp2width)];
   int i;

   for (i = 0; i < tt_context.vdp2width; i++)
      buffer[i].pixel = color;
}