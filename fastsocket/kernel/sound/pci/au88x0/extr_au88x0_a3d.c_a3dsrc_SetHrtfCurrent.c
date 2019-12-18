#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;
struct TYPE_5__ {int /*<<< orphan*/  source; int /*<<< orphan*/  slice; scalar_t__ vortex; } ;
typedef  TYPE_2__ a3dsrc_t ;
typedef  int* a3d_Hrtf_t ;

/* Variables and functions */
 int /*<<< orphan*/  A3D_B_HrtfCurrent ; 
 int HRTF_SZ ; 
 scalar_t__ a3d_addrB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
a3dsrc_SetHrtfCurrent(a3dsrc_t * a, a3d_Hrtf_t const aa, a3d_Hrtf_t const b)
{
	vortex_t *vortex = (vortex_t *) (a->vortex);
	int i;

	for (i = 0; i < HRTF_SZ; i++)
		hwwrite(vortex->mmio,
			a3d_addrB(a->slice, a->source,
				  A3D_B_HrtfCurrent) + (i << 2),
			(b[i] << 0x10) | aa[i]);
}