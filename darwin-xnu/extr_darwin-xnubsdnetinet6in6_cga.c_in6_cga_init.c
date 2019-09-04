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
struct TYPE_2__ {int /*<<< orphan*/  cga_initialized; int /*<<< orphan*/  cga_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ifa_mtx_attr ; 
 int /*<<< orphan*/  ifa_mtx_grp ; 
 TYPE_1__ in6_cga ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
in6_cga_init(void)
{
	lck_mtx_init(&in6_cga.cga_mutex, ifa_mtx_grp, ifa_mtx_attr);
	in6_cga.cga_initialized = TRUE;
}