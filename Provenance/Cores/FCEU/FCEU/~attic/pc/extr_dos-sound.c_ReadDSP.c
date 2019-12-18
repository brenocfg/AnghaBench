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
 scalar_t__ SBPort ; 
 int inportb (scalar_t__) ; 

__attribute__((used)) static int ReadDSP(uint8 *V)
{
 int x;

 for(x=65536;x;x--)             /* Should be more than enough time... */
 {
  if(inportb(SBPort+0xE)&0x80)
  {
   *V=inportb(SBPort+0xA);
   return(1);
  }
 }
 return(0);
}