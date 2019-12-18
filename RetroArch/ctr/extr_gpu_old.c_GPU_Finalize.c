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
 int /*<<< orphan*/  GPUCMD_AddMaskedWrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GPUCMD_AddWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPUCMD_Split (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GPUREG_FINALIZE ; 
 int /*<<< orphan*/  GPUREG_FRAMEBUFFER_FLUSH ; 
 int /*<<< orphan*/  GPUREG_FRAMEBUFFER_INVALIDATE ; 
 int /*<<< orphan*/  GPUREG_PRIMITIVE_CONFIG ; 

void GPU_Finalize(void)
{
   GPUCMD_AddMaskedWrite(GPUREG_PRIMITIVE_CONFIG, 0x8, 0x00000000);
   GPUCMD_AddWrite(GPUREG_FRAMEBUFFER_FLUSH, 0x00000001);
   GPUCMD_AddWrite(GPUREG_FRAMEBUFFER_INVALIDATE, 0x00000001);
#if 0
   GPUCMD_Split(NULL, NULL);
#else
   GPUCMD_AddWrite(GPUREG_FINALIZE, 0x12345678);
   //not the cleanest way of guaranteeing 0x10-byte size but whatever good enough for now
   GPUCMD_AddWrite(GPUREG_FINALIZE,0x12345678);
#endif
}