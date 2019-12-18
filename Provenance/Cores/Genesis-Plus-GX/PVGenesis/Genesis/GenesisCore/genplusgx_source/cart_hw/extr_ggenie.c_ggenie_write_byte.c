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
typedef  size_t uint8 ;
struct TYPE_2__ {int* regs; } ;

/* Variables and functions */
 TYPE_1__ ggenie ; 
 int /*<<< orphan*/  ggenie_write_regs (size_t,unsigned int) ; 

__attribute__((used)) static void ggenie_write_byte(unsigned int address, unsigned int data)
{
  /* Register offset */
  uint8 offset = (address >> 1) & 0x1f;

  /* /LWR and /UWR are used to decode writes */
  if (address & 1)
  {
    data = (ggenie.regs[offset] & 0xff00) | (data & 0xff);
  }
  else
  {
    data = (ggenie.regs[offset] & 0x00ff) | ((data & 0xff) << 8);
  }

  /* Update internal register */
  ggenie_write_regs(offset,data);
}