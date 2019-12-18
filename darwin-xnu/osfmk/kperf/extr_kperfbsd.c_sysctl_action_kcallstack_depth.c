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
struct sysctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kperf_action_get_kcallstack_depth ; 
 int /*<<< orphan*/  kperf_action_set_kcallstack_depth ; 
 int kperf_sysctl_get_set_unsigned_uint32 (struct sysctl_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sysctl_action_kcallstack_depth(struct sysctl_req *req)
{
	return kperf_sysctl_get_set_unsigned_uint32(req,
		kperf_action_get_kcallstack_depth, kperf_action_set_kcallstack_depth);
}