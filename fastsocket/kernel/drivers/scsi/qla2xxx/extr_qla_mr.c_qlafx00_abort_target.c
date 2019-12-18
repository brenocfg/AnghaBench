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
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCF_TARGET_RESET ; 
 int qlafx00_async_tm_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 

int
qlafx00_abort_target(fc_port_t *fcport, unsigned int l, int tag)
{
	return qlafx00_async_tm_cmd(fcport, TCF_TARGET_RESET, l, tag);
}