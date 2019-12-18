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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int* mchannels ; 
 int* rampchs ; 
 int /*<<< orphan*/  vortex_mix_setenablebit (int /*<<< orphan*/ *,unsigned char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_mix_setinputvolumebyte (int /*<<< orphan*/ *,unsigned char,int,int) ; 

__attribute__((used)) static void
vortex_mix_killinput(vortex_t * vortex, unsigned char mix, int mixin)
{
	rampchs[mix] &= ~(1 << mixin);
	vortex_mix_setinputvolumebyte(vortex, mix, mixin, 0x80);
	mchannels[mix] &= ~(1 << mixin);
	vortex_mix_setenablebit(vortex, mix, mixin, 0);
}