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
typedef  int /*<<< orphan*/  u32 ;
struct powernow_k8_data {int /*<<< orphan*/  currpstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_PSTATE_CTRL ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transition_pstate(struct powernow_k8_data *data, u32 pstate)
{
	wrmsr(MSR_PSTATE_CTRL, pstate, 0);
	data->currpstate = pstate;
	return 0;
}