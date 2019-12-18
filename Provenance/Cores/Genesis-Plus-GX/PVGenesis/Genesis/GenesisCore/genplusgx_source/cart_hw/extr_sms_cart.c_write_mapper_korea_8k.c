#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  mapper_8k_w (int,int) ; 
 unsigned char** z80_writemap ; 

__attribute__((used)) static void write_mapper_korea_8k(unsigned int address, unsigned char data)
{
  if (address == 0x4000)
  {
    mapper_8k_w(2,data);
    return;
  }

  if (address == 0x6000)
  {
    mapper_8k_w(3,data);
    return;
  }

  if (address == 0x8000)
  {
    mapper_8k_w(0,data);
    return;
  }

  if (address == 0xA000)
  {
    mapper_8k_w(1,data);
    return;
  }

  if (address == 0xFFFE)
  {
    mapper_8k_w(2,(data << 1) & 0xFF);
    mapper_8k_w(3,(1 + (data << 1)) & 0xFF);
  }
  else if (address == 0xFFFF)
  {
    mapper_8k_w(0,(data << 1) & 0xFF);
    mapper_8k_w(1,(1 + (data << 1)) & 0xFF);
  }

  z80_writemap[address >> 10][address & 0x03FF] = data;
}