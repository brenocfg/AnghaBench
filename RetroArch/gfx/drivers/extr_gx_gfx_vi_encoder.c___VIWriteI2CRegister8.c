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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  __VISendI2CData (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void __VIWriteI2CRegister8(u8 reg, u8 data)
{
   u8 buf[2];
   buf[0] = reg;
   buf[1] = data;
   __VISendI2CData(0xe0,buf,2);
   udelay(2);
}