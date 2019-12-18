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
struct TYPE_2__ {int /*<<< orphan*/  (* data_w ) (unsigned int,unsigned int) ;} ;

/* Variables and functions */
 unsigned int* io_reg ; 
 TYPE_1__* port ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int,unsigned int) ; 

void io_68k_write(unsigned int offset, unsigned int data)
{
  switch (offset)
  {
    case 0x01:  /* Port A Data */
    case 0x02:  /* Port B Data */
    case 0x03:  /* Port C Data */
    {
      io_reg[offset] = data;
      port[offset-1].data_w(data, io_reg[offset + 3]);
      return;
    }

    case 0x04:  /* Port A Ctrl */
    case 0x05:  /* Port B Ctrl */
    case 0x06:  /* Port C Ctrl */
    {
      if (data != io_reg[offset])
      {
        io_reg[offset] = data;
        port[offset-4].data_w(io_reg[offset-3], data);
      }
      return;
    }

    case 0x07:  /* Port A TxData */
    case 0x0A:  /* Port B TxData */
    case 0x0D:  /* Port C TxData */
    {
      io_reg[offset] = data;
      return;
    }

    case 0x09:  /* Port A S-Ctrl */
    case 0x0C:  /* Port B S-Ctrl */
    case 0x0F:  /* Port C S-Ctrl */
    {
      io_reg[offset] = data & 0xF8;
      return;
    }

    default:  /* Read-only ports */
    {
      return;
    }
  }
}