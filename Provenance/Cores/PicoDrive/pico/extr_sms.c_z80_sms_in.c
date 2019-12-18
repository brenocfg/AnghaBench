#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int io_ctl; } ;
struct TYPE_6__ {int /*<<< orphan*/  rotate; } ;
struct TYPE_5__ {unsigned char v_counter; } ;
struct TYPE_8__ {TYPE_3__ ms; TYPE_2__ m; TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_HVCNT ; 
 int /*<<< orphan*/  EL_IO ; 
 TYPE_4__ Pico ; 
 int* PicoPad ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned char) ; 
 unsigned char vdp_ctl_read () ; 
 unsigned char vdp_data_read () ; 

__attribute__((used)) static unsigned char z80_sms_in(unsigned short a)
{
  unsigned char d = 0;

  elprintf(EL_IO, "z80 port %04x read", a);
  a &= 0xc1;
  switch (a)
  {
    case 0x00:
    case 0x01:
      d = 0xff;
      break;

    case 0x40: /* V counter */
      d = Pico.video.v_counter;
      elprintf(EL_HVCNT, "V counter read: %02x", d);
      break;

    case 0x41: /* H counter */
      d = Pico.m.rotate++;
      elprintf(EL_HVCNT, "H counter read: %02x", d);
      break;

    case 0x80:
      d = vdp_data_read();
      break;

    case 0x81:
      d = vdp_ctl_read();
      break;

    case 0xc0: /* I/O port A and B */
      d = ~((PicoPad[0] & 0x3f) | (PicoPad[1] << 6));
      break;

    case 0xc1: /* I/O port B and miscellaneous */
      d = (Pico.ms.io_ctl & 0x80) | ((Pico.ms.io_ctl << 1) & 0x40) | 0x30;
      d |= ~(PicoPad[1] >> 2) & 0x0f;
      break;
  }

  elprintf(EL_IO, "ret = %02x", d);
  return d;
}