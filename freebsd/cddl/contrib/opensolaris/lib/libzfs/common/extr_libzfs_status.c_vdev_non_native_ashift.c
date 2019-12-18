#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vs_configured_ashift; scalar_t__ vs_physical_ashift; } ;
typedef  TYPE_1__ vdev_stat_t ;
typedef  int /*<<< orphan*/  uint_t ;

/* Variables and functions */
 scalar_t__ VDEV_STAT_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs_physical_ashift ; 

__attribute__((used)) static int
vdev_non_native_ashift(vdev_stat_t *vs, uint_t vsc)
{
	return (VDEV_STAT_VALID(vs_physical_ashift, vsc) &&
	    vs->vs_configured_ashift < vs->vs_physical_ashift);
}