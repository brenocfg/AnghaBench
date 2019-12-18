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
 int /*<<< orphan*/  GX_LOAD_BP_REG (int) ; 
 int /*<<< orphan*/  __GX_FlushTextureState () ; 

void GX_InvalidateTexAll()
{
	__GX_FlushTextureState();
	GX_LOAD_BP_REG(0x66001000);
	GX_LOAD_BP_REG(0x66001100);
	__GX_FlushTextureState();
}