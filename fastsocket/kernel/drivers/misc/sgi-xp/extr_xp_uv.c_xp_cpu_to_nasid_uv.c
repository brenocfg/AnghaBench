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
 int UV_PNODE_TO_NASID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_cpu_to_pnode (int) ; 

__attribute__((used)) static int
xp_cpu_to_nasid_uv(int cpuid)
{
	/* ??? Is this same as sn2 nasid in mach/part bitmaps set up by SAL? */
	return UV_PNODE_TO_NASID(uv_cpu_to_pnode(cpuid));
}