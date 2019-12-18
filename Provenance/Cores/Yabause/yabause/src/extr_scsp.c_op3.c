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
typedef  int u32 ;
struct TYPE_4__ {int address_pointer; int attenuation; int wave; int output; } ;
struct TYPE_3__ {int /*<<< orphan*/  pcm8b; } ;
struct Slot {TYPE_2__ state; TYPE_1__ regs; } ;

/* Variables and functions */
 int SoundRamReadByte (int) ; 
 int SoundRamReadWord (int) ; 

void op3(struct Slot * slot)
{
   u32 addr = (slot->state.address_pointer) & 0x7FFFF;

   if (slot->state.attenuation > 0x3bf)
      return;

   if (!slot->regs.pcm8b)
      slot->state.wave = SoundRamReadWord(addr);
   else
      slot->state.wave = SoundRamReadByte(addr) << 8;

   slot->state.output = slot->state.wave;
}