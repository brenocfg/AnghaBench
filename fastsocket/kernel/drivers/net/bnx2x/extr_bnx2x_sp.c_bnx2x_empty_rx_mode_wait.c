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
struct bnx2x_rx_mode_ramrod_params {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int bnx2x_empty_rx_mode_wait(struct bnx2x *bp,
				    struct bnx2x_rx_mode_ramrod_params *p)
{
	/* Do nothing */
	return 0;
}