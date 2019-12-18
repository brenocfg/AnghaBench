#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  DisaGetEa (char*,int,int) ; 
 int /*<<< orphan*/  DisaText ; 
 int* Tasm ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 

__attribute__((used)) static int DisaMove(int op)
{
  // Move 00xxdddD DDssssss (xx=size extension, ssssss=Source EA, DDDddd=Dest ea)
  int sea=0,dea=0;
  char inst[64]="",seat[64]="",deat[64]="";
  char *movea="";
  int size=0;

  if ((op&0x01c0)==0x0040) movea="a"; // See if it's a movea opcode

  // Find size extension
  switch (op&0x3000)
  {
    case 0x1000: size=0; break;
    case 0x3000: size=1; break;
    case 0x2000: size=2; break;
    default: return 1;
  }

  sea = op&0x003f;
  DisaGetEa(seat,sea,size);
  
  dea =(op&0x01c0)>>3;
  dea|=(op&0x0e00)>>9;
  DisaGetEa(deat,dea,size);

  sprintf(inst,"move%s.%c",movea,Tasm[size]);
  sprintf(DisaText,"%s %s, %s",inst,seat,deat);
  return 0;
}