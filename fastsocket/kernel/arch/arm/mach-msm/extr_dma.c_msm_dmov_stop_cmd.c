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
struct msm_dmov_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMOV_FLUSH0 (unsigned int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void msm_dmov_stop_cmd(unsigned id, struct msm_dmov_cmd *cmd, int graceful)
{
	writel((graceful << 31), DMOV_FLUSH0(id));
}