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

/* Variables and functions */
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int stf_init_done ; 
 int /*<<< orphan*/  stf_mtx_grp ; 

__attribute__((used)) static void
stfinit(void)
{
	if (!stf_init_done) {
		stf_mtx_grp = lck_grp_alloc_init("stf", LCK_GRP_ATTR_NULL);
		stf_init_done = 1;
	}
}