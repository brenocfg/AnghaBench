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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_hw_ver {int /*<<< orphan*/  majorVersion; int /*<<< orphan*/  minorVersion; int /*<<< orphan*/  coreVersion; } ;
struct vfe_cmd_hw_version {int /*<<< orphan*/  majorVersion; int /*<<< orphan*/  minorVersion; int /*<<< orphan*/  coreVersion; } ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_HW_VERSION ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

void vfe_get_hw_version(struct vfe_cmd_hw_version *out)
{
	uint32_t vfeHwVersionPacked;
	struct vfe_hw_ver ver;

	vfeHwVersionPacked = readl(ctrl->vfebase + VFE_HW_VERSION);

	ver = *((struct vfe_hw_ver *)&vfeHwVersionPacked);

	out->coreVersion  = ver.coreVersion;
	out->minorVersion = ver.minorVersion;
	out->majorVersion = ver.majorVersion;
}