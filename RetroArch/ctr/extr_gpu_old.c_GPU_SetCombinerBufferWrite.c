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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GPUCMD_AddMaskedWrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GPUREG_TEXENV_UPDATE_BUFFER ; 

void GPU_SetCombinerBufferWrite(u8 rgb_config, u8 alpha_config)
{
    GPUCMD_AddMaskedWrite(GPUREG_TEXENV_UPDATE_BUFFER, 0x2, (rgb_config << 8) | (alpha_config << 12));
}