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

/* Variables and functions */
 int* _viReg ; 

__attribute__((used)) static inline void __getCurrentDisplayPosition(u32 *px,u32 *py)
{
	u32 hpos = 0;
	u32 vpos = 0;
	u32 vpos_old;

	vpos = (_viReg[22]&0x7ff);
	do {
		vpos_old = vpos;
		hpos = (_viReg[23]&0x7ff);
		vpos = (_viReg[22]&0x7ff);
	} while(vpos_old!=vpos);
	*px = hpos;
	*py = vpos;
}