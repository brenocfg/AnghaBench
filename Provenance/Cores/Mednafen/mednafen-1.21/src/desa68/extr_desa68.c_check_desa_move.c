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
typedef  int u32 ;
struct TYPE_2__ {int line; int adrmode0; int adrmode6; } ;

/* Variables and functions */
 int MODE_AN ; 
 TYPE_1__ d ; 
 int /*<<< orphan*/  desa_move () ; 

__attribute__((used)) static int check_desa_move()
{
  u32 srcmsk   = 0xFFF;
  u32 destmsk  = 0x1FF;
  /* Remove An source & destination addressing mode for byte access */
  if(d.line==0x1)
    {
      srcmsk  &= ~(1<<MODE_AN);
      destmsk &= ~(1<<MODE_AN);
    }
  if((srcmsk&(1<<d.adrmode0 )) && (destmsk&(1<<d.adrmode6)) );
  {
    desa_move();
    return 1;
  }
  return 0;

}