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
 int /*<<< orphan*/  DisaGetEa (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisaText ; 
 int /*<<< orphan*/  GetOffset (char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int DisaLink(int op)
{
  // Link opcode, 01001110 01010nnn dd   link An,#offset
  char eat[64]="";
  char offset[32]="";

  DisaGetEa(eat,(op&7)|8,0);
  GetOffset(offset);

  sprintf(DisaText,"link %s,#%s",eat,offset);

  return 0;
}