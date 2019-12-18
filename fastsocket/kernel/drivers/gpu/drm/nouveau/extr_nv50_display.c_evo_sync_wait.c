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
 int /*<<< orphan*/  EVO_MAST_NTFY ; 
 int nouveau_bo_rd32 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool
evo_sync_wait(void *data)
{
	if (nouveau_bo_rd32(data, EVO_MAST_NTFY) != 0x00000000)
		return true;
	usleep_range(1, 2);
	return false;
}