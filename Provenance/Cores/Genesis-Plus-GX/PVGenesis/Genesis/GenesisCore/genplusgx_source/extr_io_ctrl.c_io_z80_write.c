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
struct TYPE_2__ {int /*<<< orphan*/  (* data_w ) (unsigned int,int) ;} ;

/* Variables and functions */
 unsigned int MCYCLES_PER_LINE ; 
 int REGION_USA ; 
 int* hctab ; 
 int hvc_latch ; 
 int* io_reg ; 
 TYPE_1__* port ; 
 int region_code ; 
 int /*<<< orphan*/  sms_cart_switch (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int,int) ; 
 int /*<<< orphan*/  stub2 (unsigned int,int) ; 

void io_z80_write(unsigned int offset, unsigned int data, unsigned int cycles)
{
  if (offset)
  {
    /* I/O Control register */
    if (region_code & REGION_USA)
    {
      /* 
        Bit  Function
        --------------
        D7 : Port B TH pin output level (1=high, 0=low)
        D6 : Port B TR pin output level (1=high, 0=low)
        D5 : Port A TH pin output level (1=high, 0=low)
        D4 : Port A TR pin output level (1=high, 0=low)
        D3 : Port B TH pin direction (1=input, 0=output)
        D2 : Port B TR pin direction (1=input, 0=output)
        D1 : Port A TH pin direction (1=input, 0=output)
        D0 : Port A TR pin direction (1=input, 0=output)
      */

      /* Send TR/TH state to connected peripherals */
      port[0].data_w((data << 1) & 0x60, (~io_reg[0x0F] << 5) & 0x60);
      port[1].data_w((data >> 1) & 0x60, (~io_reg[0x0F] << 3) & 0x60);


      /* Check for TH low-to-high transitions on both ports */
      if ((!(io_reg[0x0F] & 0x80) && (data & 0x80)) ||
          (!(io_reg[0x0F] & 0x20) && (data & 0x20)))
      {
        /* Latch new HVC */
        hvc_latch = hctab[cycles % MCYCLES_PER_LINE] | 0x10000;
     }

      /* Update I/O Control register */
      io_reg[0x0F] = data;
    }
    else
    {
      /* TH output is fixed to 0 & TR is always an input on japanese hardware */
      io_reg[0x0F] = (data | 0x05) & 0x5F;

      /* Port $DD bits D4-D5 return D0-D2 (cf. http://www2.odn.ne.jp/~haf09260/Sms/EnrSms.htm) */
      io_reg[0x0D] = ((data & 0x01) << 4) | ((data & 0x04) << 3);
    }
  }
  else
  {
    /* Update Memory Control register */
    io_reg[0x0E] = data;

    /* Switch cartridge & BIOS ROM */
    sms_cart_switch(~data);
  }
}