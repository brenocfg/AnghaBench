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
typedef  int /*<<< orphan*/  u32 ;
struct vfp_single {int sign; int exponent; int significand; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  vfp_single_normaliseround (int,struct vfp_single*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u32 vfp_single_fsito(int sd, int unused, s32 m, u32 fpscr)
{
	struct vfp_single vs;

	vs.sign = (m & 0x80000000) >> 16;
	vs.exponent = 127 + 31 - 1;
	vs.significand = vs.sign ? -m : m;

	return vfp_single_normaliseround(sd, &vs, fpscr, 0, "fsito");
}