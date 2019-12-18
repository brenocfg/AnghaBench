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
typedef  int GPU_CULLMODE ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUREG_FACECULLING_CONFIG ; 

void GPU_SetFaceCulling(GPU_CULLMODE mode)
{
	GPUCMD_AddWrite(GPUREG_FACECULLING_CONFIG, mode&0x3);
}