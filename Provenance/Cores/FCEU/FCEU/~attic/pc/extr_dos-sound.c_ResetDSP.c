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
typedef  int uint8 ;

/* Variables and functions */
 scalar_t__ ReadDSP (int*) ; 
 scalar_t__ SBPort ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  outportb (scalar_t__,int) ; 

__attribute__((used)) static int ResetDSP(void)
{
 uint8 b;

 outportb(SBPort+0x6,0x1);
 delay(10);
 outportb(SBPort+0x6,0x0);
 delay(10);

 if(ReadDSP(&b))
  if(b==0xAA)
   return(1); 
 return(0);
}