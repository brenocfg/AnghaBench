#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsp {TYPE_2__* slots; } ;
struct TYPE_4__ {scalar_t__ kb; } ;
struct TYPE_5__ {TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyoff (TYPE_2__*) ; 
 int /*<<< orphan*/  keyon (TYPE_2__*) ; 

void keyonex(struct Scsp *s)
{
   int channel;
   for (channel = 0; channel < 32; channel++)
   {
      if (s->slots[channel].regs.kb)
         keyon(&s->slots[channel]);
      else
         keyoff(&s->slots[channel]);
   }
}