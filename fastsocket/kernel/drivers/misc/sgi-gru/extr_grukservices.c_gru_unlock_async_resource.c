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
 int ASYNC_HAN_TO_BID (unsigned long) ; 
 int /*<<< orphan*/  gru_unlock_kernel_context (int) ; 

void gru_unlock_async_resource(unsigned long han)
{
	int blade_id = ASYNC_HAN_TO_BID(han);

	gru_unlock_kernel_context(blade_id);
}