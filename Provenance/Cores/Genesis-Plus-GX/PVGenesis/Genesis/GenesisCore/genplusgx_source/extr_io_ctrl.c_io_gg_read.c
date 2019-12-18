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
struct TYPE_2__ {unsigned int* pad; } ;

/* Variables and functions */
 unsigned int INPUT_START ; 
 TYPE_1__ input ; 
 unsigned int* io_reg ; 

unsigned int io_gg_read(unsigned int offset)
{
  switch (offset)
  {
    case 0: /* Mode Register */
      return (io_reg[0] & ~(input.pad[0] & INPUT_START));

    case 1: /* Parallel data register (not connected) */
      return ((io_reg[1] & ~(io_reg[2] & 0x7F)) | (io_reg[2] & 0x7F));

    case 2: /* Data direction register and NMI enable */
      return io_reg[2];

    case 3: /* Transmit data buffer */
      return io_reg[3];

    case 4: /* Receive data buffer */
      return io_reg[4];

    case 5: /* Serial control */
      return io_reg[5];

    default: /* Write-Only */
      return 0xFF;
  }
}