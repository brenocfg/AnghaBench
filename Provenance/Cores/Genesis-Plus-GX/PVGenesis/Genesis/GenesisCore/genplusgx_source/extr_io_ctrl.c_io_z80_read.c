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
struct TYPE_2__ {int (* data_r ) () ;} ;

/* Variables and functions */
 unsigned int IO_RESET_HI ; 
 unsigned int* io_reg ; 
 TYPE_1__* port ; 
 int stub1 () ; 
 int stub2 () ; 

unsigned int io_z80_read(unsigned int offset)
{
  /* Read port A & port B input data */
  unsigned int data = (port[0].data_r()) | (port[1].data_r() << 8);

  /* I/O control register value */
  unsigned int ctrl = io_reg[0x0F];

  /* I/O ports */
  if (offset)
  {
   /* 
     Bit  Function
     --------------
     D7 : Port B TH pin input
     D6 : Port A TH pin input
     D5 : CONT input (0 on Mega Drive hardware, 1 otherwise)
     D4 : RESET button (1: default, 0: pressed, only on Master System hardware)
     D3 : Port B TR pin input
     D2 : Port B TL pin input
     D1 : Port B Right pin input
     D0 : Port B Left pin input
    */
    data = ((data >> 10) & 0x0F) | (data & 0x40) | ((data >> 7) & 0x80) | io_reg[0x0D];

    /* clear !RESET input */
    io_reg[0x0D] |= IO_RESET_HI;

    /* Adjust port B TH state if configured as output */
    if (!(ctrl & 0x08))
    {
      data &= ~0x80;
      data |= (ctrl & 0x80);
    }

    /* Adjust port A TH state if configured as output */
    if (!(ctrl & 0x02))
    {
      data &= ~0x40;
      data |= ((ctrl & 0x20) << 1);
    }

    /* Adjust port B TR state if configured as output */
    if (!(ctrl & 0x04))
    {
      data &= ~0x08;
      data |= ((ctrl & 0x40) >> 3);
    }
  }
  else
  {
   /* 
     Bit  Function
     --------------
     D7 : Port B Down pin input
     D6 : Port B Up pin input
     D5 : Port A TR pin input
     D4 : Port A TL pin input
     D3 : Port A Right pin input
     D2 : Port A Left pin input
     D1 : Port A Down pin input
     D0 : Port A Up pin input
    */
    data = (data & 0x3F) | ((data >> 2) & 0xC0);

    /* Adjust port A TR state if configured as output */
    if (!(ctrl & 0x01))
    {
      data &= ~0x20;
      data |= ((ctrl & 0x10) << 1);
    }
  }

  return data;
}