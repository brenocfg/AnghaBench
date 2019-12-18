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
struct TYPE_2__ {int /*<<< orphan*/ * linescreen; int /*<<< orphan*/ * vdp2framebuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__ tt_context ; 

int TitanDeInit()
{
   int i;

   for(i = 0;i < 6;i++)
      free(tt_context.vdp2framebuffer[i]);

   for(i = 1;i < 4;i++)
      free(tt_context.linescreen[i]);

   return 0;
}