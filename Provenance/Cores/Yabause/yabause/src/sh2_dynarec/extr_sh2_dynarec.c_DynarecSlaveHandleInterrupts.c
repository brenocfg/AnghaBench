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
struct TYPE_4__ {int NumberOfInterrupts; scalar_t__ isSleeping; scalar_t__ isIdle; TYPE_1__* interrupts; } ;
struct TYPE_3__ {int level; int vector; } ;

/* Variables and functions */
 int MappedMemoryReadLong (int) ; 
 int /*<<< orphan*/  MappedMemoryWriteLong (int,int) ; 
 size_t SR ; 
 TYPE_2__* SSH2 ; 
 size_t VBR ; 
 int /*<<< orphan*/  get_addr_ht (int) ; 
 int /*<<< orphan*/  slave_ip ; 
 int slave_pc ; 
 int* slave_reg ; 

void DynarecSlaveHandleInterrupts()
{
  if (SSH2->interrupts[SSH2->NumberOfInterrupts-1].level > ((slave_reg[SR]>>4)&0xF))
  {
    slave_reg[15] -= 4;
    MappedMemoryWriteLong(slave_reg[15], slave_reg[SR]);
    slave_reg[15] -= 4;
    MappedMemoryWriteLong(slave_reg[15], slave_pc);
    slave_reg[SR] &= 0xFFFFFF0F;
    slave_reg[SR] |= (SSH2->interrupts[SSH2->NumberOfInterrupts-1].level)<<4;
    slave_pc = MappedMemoryReadLong(slave_reg[VBR] + (SSH2->interrupts[SSH2->NumberOfInterrupts-1].vector << 2));
    slave_ip = get_addr_ht(slave_pc|1);
    SSH2->NumberOfInterrupts--;
    SSH2->isIdle = 0;
    SSH2->isSleeping = 0;
  }
  //printf("DynarecSlaveHandleInterrupts pc=%x ip=%x\n",slave_pc,(int)slave_ip);
  //printf("master_cc=%d slave_cc=%d\n",master_cc,slave_cc);
}