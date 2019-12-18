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
 int ANTIC_NMIEN ; 
 int ANTIC_NMIST ; 
 int /*<<< orphan*/  ANTIC_OFFSET_DMACTL ; 
 int /*<<< orphan*/  ANTIC_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ANTIC_Reset(void)
{
	ANTIC_NMIEN = 0x00;
	ANTIC_NMIST = 0x1f;
	ANTIC_PutByte(ANTIC_OFFSET_DMACTL, 0);
}