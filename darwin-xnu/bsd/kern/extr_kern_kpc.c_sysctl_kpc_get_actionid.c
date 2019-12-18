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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int kpc_get_actionid (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
sysctl_kpc_get_actionid(uint32_t classes, void* buf)
{
	return kpc_get_actionid( classes, buf );
}