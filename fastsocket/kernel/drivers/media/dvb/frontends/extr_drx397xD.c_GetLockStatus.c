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
struct TYPE_2__ {int d60; } ;
struct drx397xD_state {TYPE_1__ config; } ;

/* Variables and functions */
 int RD16 (struct drx397xD_state*,int) ; 

__attribute__((used)) static int GetLockStatus(struct drx397xD_state *s, int *lockstat)
{
	int rc;

	*lockstat = 0;

	rc = RD16(s, 0x082004b);
	if (rc < 0)
		return rc;

	if (s->config.d60 != 2)
		return 0;

	if ((rc & 7) == 7)
		*lockstat |= 1;
	if ((rc & 3) == 3)
		*lockstat |= 2;
	if (rc & 1)
		*lockstat |= 4;
	return 0;
}