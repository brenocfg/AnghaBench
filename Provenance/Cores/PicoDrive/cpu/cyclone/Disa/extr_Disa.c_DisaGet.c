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
 scalar_t__* Comment ; 
 int DisaPc ; 
 scalar_t__* DisaText ; 
 int DisaWord (int) ; 
 int /*<<< orphan*/  TryOp (int) ; 
 int /*<<< orphan*/  strcat (scalar_t__*,scalar_t__*) ; 

int DisaGet()
{
  int op=0;
  if (DisaWord==NULL) return 1;

  Comment[0]=0;
  DisaText[0]=0; // Assume opcode unknown

  op=DisaWord(DisaPc)&0xffff; DisaPc+=2;
  TryOp(op);
  strcat(DisaText,Comment);

  // Unknown opcoode
  return 0;
}