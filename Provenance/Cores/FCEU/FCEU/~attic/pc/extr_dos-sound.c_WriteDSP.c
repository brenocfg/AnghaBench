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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 scalar_t__ SBPort ; 
 int inportb (scalar_t__) ; 
 int /*<<< orphan*/  outportb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WriteDSP(uint8 V)
{
 int x;

 for(x=65536;x;x--)
 {
  if(!(inportb(SBPort+0xC)&0x80))
  {
   outportb(SBPort+0xC,V);
   return(1);
  }
 }
 return(0);
}