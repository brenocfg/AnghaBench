#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int* mousebits; } ;
struct TYPE_4__ {int* data; } ;
typedef  TYPE_1__ PortData_struct ;
typedef  TYPE_2__ PerMouse_struct ;

/* Variables and functions */

void PerFlush(PortData_struct * port)
{
   /* FIXME this function only flush data if there's a mouse connected as
    * first peripheral */
  u8 perid = port->data[1];
  if (perid == 0xE3)
  {
     PerMouse_struct * mouse = (PerMouse_struct *) (port->data + 1);

     mouse->mousebits[0] &= 0x0F;
     mouse->mousebits[1] = 0;
     mouse->mousebits[2] = 0;
  }
}