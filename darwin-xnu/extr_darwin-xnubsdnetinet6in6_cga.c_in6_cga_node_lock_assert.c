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
struct TYPE_2__ {int /*<<< orphan*/  cga_mutex; int /*<<< orphan*/  cga_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 TYPE_1__ in6_cga ; 

__attribute__((used)) static void
in6_cga_node_lock_assert(int owned)
{
#if !MACH_ASSERT
#pragma unused(owned)
#endif
	VERIFY(in6_cga.cga_initialized);
	LCK_MTX_ASSERT(&in6_cga.cga_mutex, owned);
}