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
struct TYPE_2__ {unsigned char State; int Counter; int Wait; } ;

/* Variables and functions */
 TYPE_1__ mouse ; 

void mouse_write(unsigned char data, unsigned char mask)
{
  /* update bits set as output only */
  data = (mouse.State & ~mask) | (data & mask);

  /* TH transition */
  if ((mouse.State ^ data) & 0x40)
  {
    /* start (TH=0) or stop (TH=1) acquisition */
    mouse.Counter = 1 - ((data & 0x40) >> 6);
  }

  /* TR transition */
  if ((mouse.State ^ data) & 0x20)
  {
    /* acquisition in progress */
    if ((mouse.Counter > 0) && (mouse.Counter < 10))
    {
      /* increment phase */
      mouse.Counter++;
    }

    /* TL handshake latency */
    mouse.Wait = 1;
  }

  /* update internal state */
  mouse.State = data;
}