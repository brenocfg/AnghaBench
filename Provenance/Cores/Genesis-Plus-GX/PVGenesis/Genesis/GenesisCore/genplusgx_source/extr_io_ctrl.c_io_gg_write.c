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
struct TYPE_4__ {int /*<<< orphan*/  cycles; } ;
struct TYPE_3__ {int /*<<< orphan*/  psgBoostNoise; int /*<<< orphan*/  psg_preamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SN76489_Config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__ Z80 ; 
 TYPE_1__ config ; 
 unsigned int* io_reg ; 

void io_gg_write(unsigned int offset, unsigned int data)
{
  switch (offset)
  {
    case 1: /* Parallel data register */
      io_reg[1] = data;
      return;

    case 2: /* Data direction register and NMI enable */
      io_reg[2] = data;
      return;

    case 3: /* Transmit data buffer */
      io_reg[3] = data;
      return;

    case 5: /* Serial control (bits 0-2 are read-only) */
      io_reg[5] = data & 0xF8;
      return;

    case 6: /* PSG Stereo output control */
      io_reg[6] = data;
      SN76489_Config(Z80.cycles, config.psg_preamp, config.psgBoostNoise, data);
      return;

    default: /* Read-only */
      return;
  }
}