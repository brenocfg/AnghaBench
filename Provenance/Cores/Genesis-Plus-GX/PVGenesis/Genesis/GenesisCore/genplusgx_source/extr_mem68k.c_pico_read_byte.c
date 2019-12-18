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
struct TYPE_2__ {unsigned int* pad; int** analog; } ;

/* Variables and functions */
 TYPE_1__ input ; 
 unsigned int m68k_read_bus_8 (unsigned int) ; 
 int pico_current ; 
 int region_code ; 

unsigned int pico_read_byte(unsigned int address)
{
  switch (address & 0xFF)
  {
    case 0x01:  /* VERSION register */
    {
      return (region_code >> 1);
    }

    case 0x03:  /* IO register */
    {
      return ~input.pad[0];
    }

    case 0x05:  /* PEN X coordinate (MSB) */
    {
      return (input.analog[0][0] >> 8);
    }

    case 0x07:  /* PEN X coordinate (LSB) */
    {
      return (input.analog[0][0] & 0xFF);
    }

    case 0x09:  /* PEN Y coordinate (MSB) */
    {
      return (input.analog[0][1] >> 8);
    }

    case 0x0B:  /* PEN Y coordinate (LSB) */
    {
      return (input.analog[0][1] & 0xFF);
    }

    case 0x0D:  /* PAGE register */
    {
      return (1 << pico_current) - 1;
    }

    case 0x10:  /* ADPCM data registers (TODO) */
    case 0x11:
    {
      return 0xff;
    }

    case 0x12:  /* ADPCM control registers (TODO) */
    {
      return 0x80;
    }

    default:
    {
      return m68k_read_bus_8(address);
    }
  }
}