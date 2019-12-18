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
struct TYPE_2__ {unsigned int address; unsigned int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPLLWriteReg (unsigned int,unsigned int) ; 
 TYPE_1__ ym2413 ; 

void YM2413Write(unsigned int a, unsigned int v)
{
  if( !(a&2) )
  {
    if( !(a&1) )
    {
      /* address port */
      ym2413.address = v & 0xff;
    }
    else
    {
      /* data port */
      OPLLWriteReg(ym2413.address,v);
    }
  }
  else
  {
    /* latched bit (Master System specific) */
    ym2413.status = v & 0x01;
  }
}