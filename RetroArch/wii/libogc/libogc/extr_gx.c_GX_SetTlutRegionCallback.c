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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  GXTlutRegionCallback ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlut_regionCB ; 

GXTlutRegionCallback GX_SetTlutRegionCallback(GXTlutRegionCallback cb)
{
	u32 level;
	GXTlutRegionCallback ret;

	_CPU_ISR_Disable(level);
	ret = tlut_regionCB;
	tlut_regionCB = cb;
	_CPU_ISR_Restore(level);

	return ret;
}