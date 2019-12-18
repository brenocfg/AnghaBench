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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void __buildchecksum(u16 *buffer,u16 *c1,u16 *c2)
{
	u32 i;

	*c1 = 0;
	*c2 = 0;
	for(i=0;i<4;i++) {
		*c1 += buffer[6+i];
		*c2 += buffer[6+i]^-1;
	}
}