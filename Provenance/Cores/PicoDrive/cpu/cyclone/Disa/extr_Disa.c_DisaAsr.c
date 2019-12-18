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
 char** AsrName ; 
 int /*<<< orphan*/  DisaText ; 
 int* Tasm ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char,int,char,int,int) ; 

__attribute__((used)) static int DisaAsr(int op)
{
  // Asr/l/Ror/l etc - 1110cccd xxuttnnn
  // (ccc=count, d=direction xx=size extension, u=use reg for count, tt=type, nnn=register Dn)
  int count=0,dir=0,size=0,usereg=0,type=0,num=0;

  count =(op>>9)&7;
  dir   =(op>>8)&1;
  size  =(op>>6)&3; if (size>=3) return 1; // todo Asr EA
  usereg=(op>>5)&1;
  type  =(op>>3)&3;
  num   = op    &7; // Register number

  if (usereg==0) count=((count-1)&7)+1; // because ccc=000 means 8

  sprintf(DisaText,"%s%c.%c %c%d, d%d",
    AsrName[type], dir?'l':'r', Tasm[size],
    usereg?'d':'#', count, num);
  return 0;
}