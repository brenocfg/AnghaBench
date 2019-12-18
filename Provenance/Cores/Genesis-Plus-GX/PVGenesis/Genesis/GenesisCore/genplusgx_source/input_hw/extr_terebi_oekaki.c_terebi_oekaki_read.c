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
typedef  int uint16 ;
struct TYPE_4__ {int** analog; int* pad; } ;
struct TYPE_3__ {int busy; size_t axis; } ;

/* Variables and functions */
 int INPUT_B ; 
 TYPE_2__ input ; 
 TYPE_1__ tablet ; 

unsigned short terebi_oekaki_read(void)
{
  uint16 data = (tablet.busy << 15) | input.analog[0][tablet.axis];

  if (!(input.pad[0] & INPUT_B))
  {
    data |= 0x100;
  }

  /* clear BUSY flag */
  tablet.busy = 0;

  return data;
}