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
typedef  int GPU_TEXUNIT ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddMaskedWrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_SH_OUTATTR_CLOCK ; 
 int /*<<< orphan*/  GPUREG_TEXUNIT_CONFIG ; 

void GPU_SetTextureEnable(GPU_TEXUNIT units)
{
	GPUCMD_AddMaskedWrite(GPUREG_SH_OUTATTR_CLOCK, 0x2, units<<8); // enables texcoord outputs
	GPUCMD_AddWrite(GPUREG_TEXUNIT_CONFIG, 0x00011000|units); // enables texture units
}