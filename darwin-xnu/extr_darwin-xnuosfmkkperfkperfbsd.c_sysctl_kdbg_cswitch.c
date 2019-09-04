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
 int /*<<< orphan*/  kperf_kdbg_cswitch_get ; 
 int /*<<< orphan*/  kperf_kdbg_cswitch_set ; 
 int kperf_sysctl_get_set_int (struct sysctl_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sysctl_kdbg_cswitch(struct sysctl_req *req)
{
	return kperf_sysctl_get_set_int(req, kperf_kdbg_cswitch_get,
		kperf_kdbg_cswitch_set);
}