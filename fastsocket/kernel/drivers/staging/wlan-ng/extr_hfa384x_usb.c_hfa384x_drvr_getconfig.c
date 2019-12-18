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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int hfa384x_dorrid_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int hfa384x_drvr_getconfig(hfa384x_t *hw, u16 rid, void *buf, u16 len)
{
	int result;

	result = hfa384x_dorrid_wait(hw, rid, buf, len);

	return result;
}