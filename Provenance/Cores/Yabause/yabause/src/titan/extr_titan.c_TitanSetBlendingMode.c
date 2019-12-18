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
struct TYPE_2__ {void* trans; int /*<<< orphan*/  blend; } ;

/* Variables and functions */
 int TITAN_BLEND_ADD ; 
 int TITAN_BLEND_BOTTOM ; 
 int /*<<< orphan*/  TitanBlendPixelsAdd ; 
 int /*<<< orphan*/  TitanBlendPixelsBottom ; 
 int /*<<< orphan*/  TitanBlendPixelsTop ; 
 void* TitanTransAlpha ; 
 void* TitanTransBit ; 
 TYPE_1__ tt_context ; 

void TitanSetBlendingMode(int blend_mode)
{
   if (blend_mode == TITAN_BLEND_BOTTOM)
   {
      tt_context.blend = TitanBlendPixelsBottom;
      tt_context.trans = TitanTransBit;
   }
   else if (blend_mode == TITAN_BLEND_ADD)
   {
      tt_context.blend = TitanBlendPixelsAdd;
      tt_context.trans = TitanTransBit;
   }
   else
   {
      tt_context.blend = TitanBlendPixelsTop;
      tt_context.trans = TitanTransAlpha;
   }
}