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
 int /*<<< orphan*/  GX_LOAD_CP_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GX_ClearVCacheMetric()
{
	GX_LOAD_CP_REG(0,0);
}