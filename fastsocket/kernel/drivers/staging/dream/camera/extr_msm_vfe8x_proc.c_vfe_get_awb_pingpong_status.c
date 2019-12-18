#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int VFE_AWB_PINGPONG_STATUS_BIT ; 
 scalar_t__ VFE_BUS_PINGPONG_STATUS ; 
 TYPE_1__* ctrl ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static boolean vfe_get_awb_pingpong_status(void)
{
	uint32_t busPingPongStatus;

	busPingPongStatus =
		readl(ctrl->vfebase + VFE_BUS_PINGPONG_STATUS);

	if ((busPingPongStatus & VFE_AWB_PINGPONG_STATUS_BIT) == 0)
		return FALSE;

	return TRUE;
}