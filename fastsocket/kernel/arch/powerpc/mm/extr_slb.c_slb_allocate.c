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
 int /*<<< orphan*/  slb_allocate_realmode (unsigned long) ; 

__attribute__((used)) static void slb_allocate(unsigned long ea)
{
	/* Currently, we do real mode for all SLBs including user, but
	 * that will change if we bring back dynamic VSIDs
	 */
	slb_allocate_realmode(ea);
}