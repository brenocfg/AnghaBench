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
 int /*<<< orphan*/  STATE_FRESH ; 
 int /*<<< orphan*/  __device_refresh () ; 
 int __wait_latch (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __device_refresh_sync(void)
{
	__device_refresh();
	return __wait_latch(0x1604, STATE_FRESH);
}