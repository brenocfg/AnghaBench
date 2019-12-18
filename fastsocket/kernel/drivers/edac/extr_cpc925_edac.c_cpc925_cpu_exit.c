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
struct cpc925_dev_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void cpc925_cpu_exit(struct cpc925_dev_info *dev_info)
{
	/*
	 * WARNING:
	 * We are supposed to clear the CPU error detection bits,
	 * and it will be no problem to do so. However, once they
	 * are cleared here if we want to re-install CPC925 EDAC
	 * module later, setting them up in cpc925_cpu_init() will
	 * trigger machine check exception.
	 * Also, it's ok to leave CPU error detection bits enabled,
	 * since they are reset to 1 by default.
	 */

	return;
}