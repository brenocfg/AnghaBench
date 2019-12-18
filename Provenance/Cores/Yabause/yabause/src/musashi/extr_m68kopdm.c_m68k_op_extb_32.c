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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int DY ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 scalar_t__ GET_MSB_8 (int) ; 
 int MASK_OUT_ABOVE_8 (int) ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 

void m68k_op_extb_32(void)
{
	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint* r_dst = &DY;

		*r_dst = MASK_OUT_ABOVE_8(*r_dst) | (GET_MSB_8(*r_dst) ? 0xffffff00 : 0);

		FLAG_N = NFLAG_32(*r_dst);
		FLAG_Z = *r_dst;
		FLAG_V = VFLAG_CLEAR;
		FLAG_C = CFLAG_CLEAR;
		return;
	}
	m68ki_exception_illegal();
}