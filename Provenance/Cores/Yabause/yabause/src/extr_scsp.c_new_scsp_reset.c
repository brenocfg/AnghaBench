#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Scsp {TYPE_2__* slots; } ;
struct TYPE_3__ {int attenuation; int num; int /*<<< orphan*/  envelope; } ;
struct TYPE_4__ {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  ScspDsp ;

/* Variables and functions */
 int /*<<< orphan*/  RELEASE ; 
 int /*<<< orphan*/  fill_alfo_tables () ; 
 int /*<<< orphan*/  fill_plfo_tables () ; 
 int /*<<< orphan*/  memset (struct Scsp*,int /*<<< orphan*/ ,int) ; 
 struct Scsp scsp_dsp ; 

void new_scsp_reset(struct Scsp* s)
{
   int slot_num;
   memset(s, 0, sizeof(struct Scsp));

   for (slot_num = 0; slot_num < 32; slot_num++)
   {
      s->slots[slot_num].state.attenuation = 0x3FF;
      s->slots[slot_num].state.envelope = RELEASE;
      s->slots[slot_num].state.num = slot_num;
   }

   fill_plfo_tables();
   fill_alfo_tables();

   memset(&scsp_dsp, 0, sizeof(ScspDsp));

}