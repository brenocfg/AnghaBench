#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  regs ;
struct TYPE_5__ {int ax; int cx; int dx; } ;
struct TYPE_6__ {TYPE_1__ x; } ;
typedef  TYPE_2__ __dpmi_regs ;

/* Variables and functions */
 int /*<<< orphan*/  __dpmi_int (int,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int InitMouse(void)
{
 __dpmi_regs regs;

 memset(&regs,0,sizeof(regs));
 regs.x.ax=0;
 __dpmi_int(0x33,&regs);
 if(regs.x.ax!=0xFFFF)
  return(0);

 memset(&regs,0,sizeof(regs));
 regs.x.ax=0x7;
 regs.x.cx=0;           // Min X
 regs.x.dx=260;         // Max X
 __dpmi_int(0x33,&regs);

 memset(&regs,0,sizeof(regs));
 regs.x.ax=0x8;
 regs.x.cx=0;           // Min Y
 regs.x.dx=260;         // Max Y
 __dpmi_int(0x33,&regs);

 memset(&regs,0,sizeof(regs));
 regs.x.ax=0xF;
 regs.x.cx=8;           // Mickey X
 regs.x.dx=8;           // Mickey Y
 __dpmi_int(0x33,&regs);

 memset(&regs,0,sizeof(regs));
 regs.x.ax=0x2;
 __dpmi_int(0x33,&regs);

 return(1);
}