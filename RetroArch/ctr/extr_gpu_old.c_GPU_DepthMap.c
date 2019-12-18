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
 int /*<<< orphan*/  GPUREG_DEPTHMAP_ENABLE ; 
 int /*<<< orphan*/  GPUREG_DEPTHMAP_OFFSET ; 
 int /*<<< orphan*/  GPUREG_DEPTHMAP_SCALE ; 
 int f32tof24 (float) ; 

void GPU_DepthMap(float zScale, float zOffset)
{
	GPUCMD_AddWrite(GPUREG_DEPTHMAP_ENABLE, 0x00000001);
	GPUCMD_AddWrite(GPUREG_DEPTHMAP_SCALE, f32tof24(zScale));
	GPUCMD_AddWrite(GPUREG_DEPTHMAP_OFFSET, f32tof24(zOffset));
}