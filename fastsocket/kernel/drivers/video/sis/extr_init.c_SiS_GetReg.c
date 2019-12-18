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
typedef  scalar_t__ SISIOADDRESS ;

/* Variables and functions */
 unsigned char InPortByte (scalar_t__) ; 
 int /*<<< orphan*/  OutPortByte (scalar_t__,unsigned short) ; 

unsigned char
SiS_GetReg(SISIOADDRESS port, unsigned short index)
{
   OutPortByte(port, index);
   return(InPortByte(port + 1));
}