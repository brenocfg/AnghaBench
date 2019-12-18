#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
struct TYPE_6__ {unsigned int*** lut_prio; } ;
struct TYPE_5__ {int /*<<< orphan*/ * word_ram; TYPE_1__* regs; } ;
struct TYPE_4__ {int w; } ;

/* Variables and functions */
 size_t READ_BYTE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  WRITE_BYTE (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 TYPE_3__ gfx ; 
 TYPE_2__ scd ; 

void dot_ram_1_write16(unsigned int address, unsigned int data)
{
  uint8 prev;
  address = (address >> 1) & 0x1ffff;
  prev = READ_BYTE(scd.word_ram[1], address);
  data = (data & 0x0f) | ((data >> 4) & 0xf0);
  data = gfx.lut_prio[(scd.regs[0x02>>1].w >> 3) & 0x03][prev][data];
  WRITE_BYTE(scd.word_ram[1], address, data);
}