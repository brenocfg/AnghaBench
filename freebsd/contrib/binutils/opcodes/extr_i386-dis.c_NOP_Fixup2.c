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
 int /*<<< orphan*/  OP_IMREG (int,int) ; 
 int PREFIX_DATA ; 
 scalar_t__ address_mode ; 
 scalar_t__ mode_64bit ; 
 int prefixes ; 
 int rex ; 

__attribute__((used)) static void
NOP_Fixup2 (int bytemode, int sizeflag)
{
  if ((prefixes & PREFIX_DATA) != 0
      || (rex != 0
	  && rex != 0x48
	  && address_mode == mode_64bit))
    OP_IMREG (bytemode, sizeflag);
}