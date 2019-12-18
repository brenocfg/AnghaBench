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
 int /*<<< orphan*/  SPRN_PVR ; 
 int mfspr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ppc440spe_revA(void)
{
	/* Catch both 440SPe variants, with and without RAID6 support */
        if ((mfspr(SPRN_PVR) & 0xffefffff) == 0x53421890)
                return 1;
        else
                return 0;
}