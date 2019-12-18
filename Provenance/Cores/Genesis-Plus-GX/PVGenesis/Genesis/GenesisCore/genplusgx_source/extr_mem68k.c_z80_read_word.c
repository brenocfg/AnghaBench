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
 unsigned int z80_read_byte (unsigned int) ; 

unsigned int z80_read_word(unsigned int address)
{
  unsigned int data = z80_read_byte(address);
  return (data | (data << 8));
}