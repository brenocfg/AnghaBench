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
typedef  void* u64 ;
struct runtime_sc {int /*<<< orphan*/  ism2; int /*<<< orphan*/  sm2; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  ism1; int /*<<< orphan*/  sm1; void* y; void* x; } ;
struct internal_sc {int /*<<< orphan*/  ism2; int /*<<< orphan*/  sm2; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  ism1; int /*<<< orphan*/  sm1; } ;

/* Variables and functions */

__attribute__((used)) static void
rtsc_init(struct runtime_sc *rtsc, struct internal_sc *isc, u64 x, u64 y)
{
	rtsc->x	   = x;
	rtsc->y    = y;
	rtsc->sm1  = isc->sm1;
	rtsc->ism1 = isc->ism1;
	rtsc->dx   = isc->dx;
	rtsc->dy   = isc->dy;
	rtsc->sm2  = isc->sm2;
	rtsc->ism2 = isc->ism2;
}