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
struct TYPE_2__ {unsigned int* regs; } ;

/* Variables and functions */
 TYPE_1__ ggenie ; 

__attribute__((used)) static unsigned int ggenie_read_byte(unsigned int address)
{
  unsigned int data = ggenie.regs[(address >> 1) & 0x1f];
  return ((address & 1) ? (data & 0xff) : ((data >> 8) & 0xff));
}