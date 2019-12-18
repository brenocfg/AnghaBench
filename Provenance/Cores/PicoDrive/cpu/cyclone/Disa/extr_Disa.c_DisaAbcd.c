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
 int /*<<< orphan*/  DisaText ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 

__attribute__((used)) static int DisaAbcd(int op)
{
  // 1t00ddd1 0000asss - sbcd/abcd Ds,Dd or -(As),-(Ad)
  int type=0;
  int dn=0,addr=0,sn=0;
  char *opcode[]={"sbcd","abcd"};

  type=(op>>14)&1;
  dn  =(op>> 9)&7;
  addr=(op>> 3)&1;
  sn  = op     &7;

  if (addr) sprintf(DisaText,"%s -(a%d), -(a%d)",opcode[type],sn,dn);
  else      sprintf(DisaText,"%s d%d, d%d",       opcode[type],sn,dn);

  return 0;
}