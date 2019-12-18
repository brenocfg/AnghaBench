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
struct TYPE_4__ {scalar_t__* dev; } ;
struct TYPE_3__ {int* Table; } ;

/* Variables and functions */
 scalar_t__ DEVICE_PAD3B ; 
 TYPE_2__ input ; 
 TYPE_1__* teamplayer ; 

void teamplayer_init(int port)
{
  int i,padnum;
  int index = 0;

  /* this table determines which gamepad input should be returned during acquisition sequence
     index  = teamplayer read table index: 0=1st read, 1=2nd read, ...
     table  = high bits are pad index, low bits are pad input shift: 0=RLDU, 4=SABC, 8=MXYZ
  */  
  for (i=0; i<4; i++)
  {
    padnum = (4 * port) + i;
    if (input.dev[padnum] == DEVICE_PAD3B)
    {
      padnum = padnum << 4;
      teamplayer[port].Table[index++] = padnum;
      teamplayer[port].Table[index++] = padnum | 4;
    }
    else
    {
      padnum = padnum << 4;
      teamplayer[port].Table[index++] = padnum;
      teamplayer[port].Table[index++] = padnum | 4;
      teamplayer[port].Table[index++] = padnum | 8;
    }
  }
}