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
 int /*<<< orphan*/  DEFAULT_TEMP_POOL_SIZE ; 
 int /*<<< orphan*/  SCE_GXM_MULTISAMPLE_NONE ; 
 int vita2d_init_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vita2d_init()
{
	return vita2d_init_internal(DEFAULT_TEMP_POOL_SIZE, SCE_GXM_MULTISAMPLE_NONE);
}