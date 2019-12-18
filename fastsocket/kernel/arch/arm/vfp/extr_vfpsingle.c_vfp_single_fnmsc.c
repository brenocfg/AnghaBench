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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int NEG_MULTIPLY ; 
 int NEG_SUBTRACT ; 
 int /*<<< orphan*/  vfp_single_multiply_accumulate (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static u32 vfp_single_fnmsc(int sd, int sn, s32 m, u32 fpscr)
{
	return vfp_single_multiply_accumulate(sd, sn, m, fpscr, NEG_SUBTRACT | NEG_MULTIPLY, "fnmsc");
}