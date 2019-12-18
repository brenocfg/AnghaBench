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
struct PixelData {int dummy; } ;
struct TYPE_2__ {int vdp2height; int vdp2width; int /*<<< orphan*/ * vdp2framebuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ tt_context ; 
 scalar_t__ vdp2_interlace ; 

void TitanErase()
{
   int i = 0;

   int height = tt_context.vdp2height;

   if (vdp2_interlace)
      height /= 2;

   for (i = 0; i < 6; i++)
      memset(tt_context.vdp2framebuffer[i], 0, sizeof(struct PixelData) * tt_context.vdp2width * height);
}