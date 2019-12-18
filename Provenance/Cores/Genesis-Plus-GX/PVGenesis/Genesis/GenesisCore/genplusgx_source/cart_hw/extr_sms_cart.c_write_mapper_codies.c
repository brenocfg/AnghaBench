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
 int /*<<< orphan*/  mapper_16k_w (int,unsigned char) ; 
 unsigned char** z80_writemap ; 

__attribute__((used)) static void write_mapper_codies(unsigned int address, unsigned char data)
{
  if (address == 0x0000)
  {
    mapper_16k_w(1,data);
    return;
  }

  if (address == 0x4000)
  {
    mapper_16k_w(2,data);
    return;
  }

  if (address == 0x8000)
  {
    mapper_16k_w(3,data);
    return;
  }

  z80_writemap[address >> 10][address & 0x03FF] = data;
}