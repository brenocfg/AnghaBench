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
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_EARLYDEPTH_CLEAR ; 
 int /*<<< orphan*/  GPUREG_FRAMEBUFFER_FLUSH ; 
 int /*<<< orphan*/  GPUREG_FRAMEBUFFER_INVALIDATE ; 

void GPU_FinishDrawing()
{
	GPUCMD_AddWrite(GPUREG_FRAMEBUFFER_FLUSH, 0x00000001);
	GPUCMD_AddWrite(GPUREG_FRAMEBUFFER_INVALIDATE, 0x00000001);
	GPUCMD_AddWrite(GPUREG_EARLYDEPTH_CLEAR, 0x00000001);
}