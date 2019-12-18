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
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int) ; 

void printregs(int edi,int esi,int ebp,int esp,int b,int d,int c,int a)
{
  printf("regs: %x %x %x %x %x %x %x (%x)\n",a,b,c,d,ebp,esi,edi,(&edi)[-1]);
}