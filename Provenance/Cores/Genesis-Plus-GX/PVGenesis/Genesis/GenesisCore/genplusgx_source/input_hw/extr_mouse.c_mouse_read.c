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
struct TYPE_4__ {int** analog; int* pad; } ;
struct TYPE_3__ {size_t Port; int Counter; int State; scalar_t__ Wait; } ;

/* Variables and functions */
 TYPE_2__ input ; 
 TYPE_1__ mouse ; 

unsigned char mouse_read()
{
  unsigned int temp = 0x00;
  int x = input.analog[mouse.Port][0];
  int y = input.analog[mouse.Port][1];

  switch (mouse.Counter)
  {
    case 0: /* initial */
      temp = 0x00;
      break;

    case 1: /* xxxx1011 */
      temp = 0x0B;
      break;

    case 2: /* xxxx1111 */
      temp = 0x0F;
      break;

    case 3: /* xxxx1111 */
      temp = 0x0F;
      break;

    case 4: /* Axis sign & overflow (not emulated) bits */
      temp |= (x < 0);
      temp |= (y < 0) << 1;
      /*
      temp |= (abs(x) > 255) << 2;
      temp |= (abs(y) > 255) << 3;
      */
      break;

    case 5: /* START, A, B, C buttons state (active high) */
      temp = (input.pad[mouse.Port] >> 4) & 0x0F;
      break;

    case 6: /* X Axis MSB */
      temp = (x >> 4) & 0x0F;
      break;
      
    case 7: /* X Axis LSB */
      temp = (x & 0x0F);
      break;

    case 8: /* Y Axis MSB */
      temp = (y >> 4) & 0x0F;
      break;
      
    case 9: /* Y Axis LSB */
      temp = (y & 0x0F);
      break;
  }

  /* TL = busy status */
  if (mouse.Wait)
  {
    /* wait before ACK, fix some buggy mouse routine (Cannon Fodder, Shangai 2, Wack World,...) */
    mouse.Wait = 0;

    /* TL = !TR */
    temp |= (~mouse.State & 0x20) >> 1;
  }
  else
  {
    /* TL = TR (data is ready) */
    temp |= (mouse.State & 0x20) >> 1;
  }

  return temp;
}