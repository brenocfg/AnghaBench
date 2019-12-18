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
 int /*<<< orphan*/  D1FF_LATCH ; 
 int /*<<< orphan*/  PBI_D6D7ram ; 
 int /*<<< orphan*/  PBI_IRQ ; 
 int /*<<< orphan*/  StateSav_ReadINT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,int) ; 

void PBI_StateRead(void)
{
	StateSav_ReadUBYTE(&D1FF_LATCH, 1);
	StateSav_ReadINT(&PBI_D6D7ram, 1);
	StateSav_ReadINT(&PBI_IRQ, 1);
}