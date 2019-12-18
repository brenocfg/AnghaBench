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
struct revmodel {float wet1; float wet; float width; scalar_t__ mode; float roomsize1; float damp1; float roomsize; float damp; TYPE_1__* combL; int /*<<< orphan*/  gain; } ;
struct TYPE_2__ {float feedback; float damp1; float damp2; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixedgain ; 
 scalar_t__ freezemode ; 
 int /*<<< orphan*/  muted ; 
 int numcombs ; 

__attribute__((used)) static void revmodel_update(struct revmodel *rev)
{
   int i;
   rev->wet1 = rev->wet * (rev->width / 2.0f + 0.5f);

   if (rev->mode >= freezemode)
   {
      rev->roomsize1 = 1.0f;
      rev->damp1 = 0.0f;
      rev->gain = muted;
   }
   else
   {
      rev->roomsize1 = rev->roomsize;
      rev->damp1 = rev->damp;
      rev->gain = fixedgain;
   }

   for (i = 0; i < numcombs; i++)
   {
      rev->combL[i].feedback = rev->roomsize1;
      rev->combL[i].damp1 = rev->damp1;
      rev->combL[i].damp2 = 1.0f - rev->damp1;
   }
}