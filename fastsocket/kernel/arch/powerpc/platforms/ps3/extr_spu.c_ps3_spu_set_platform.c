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
 int /*<<< orphan*/ * spu_management_ops ; 
 int /*<<< orphan*/  spu_management_ps3_ops ; 
 int /*<<< orphan*/ * spu_priv1_ops ; 
 int /*<<< orphan*/  spu_priv1_ps3_ops ; 

void ps3_spu_set_platform(void)
{
	spu_priv1_ops = &spu_priv1_ps3_ops;
	spu_management_ops = &spu_management_ps3_ops;
}