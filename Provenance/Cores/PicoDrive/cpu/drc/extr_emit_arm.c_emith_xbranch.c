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

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_STATUS ; 
 int EL_SVP ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOP_ADD_IMM (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_C_AM2_IMM (int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOP_C_B (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_SIMPLE (int,int) ; 
 int /*<<< orphan*/  elprintf (int,char*,void*,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int is_offset_24 (int) ; 
 scalar_t__ tcache_ptr ; 

__attribute__((used)) static int emith_xbranch(int cond, void *target, int is_call)
{
	int val = (u32 *)target - (u32 *)tcache_ptr - 2;
	int direct = is_offset_24(val);
	u32 *start_ptr = (u32 *)tcache_ptr;

	if (direct)
	{
		EOP_C_B(cond,is_call,val & 0xffffff);		// b, bl target
	}
	else
	{
#ifdef __EPOC32__
//		elprintf(EL_SVP, "emitting indirect jmp %08x->%08x", tcache_ptr, target);
		if (is_call)
			EOP_ADD_IMM(14,15,0,8);			// add lr,pc,#8
		EOP_C_AM2_IMM(cond,1,0,1,15,15,0);		// ldrcc pc,[pc]
		EOP_MOV_REG_SIMPLE(15,15);			// mov pc, pc
		EMIT((u32)target);
#else
		// should never happen
		elprintf(EL_STATUS|EL_SVP|EL_ANOMALY, "indirect jmp %08x->%08x", target, tcache_ptr);
		exit(1);
#endif
	}

	return (u32 *)tcache_ptr - start_ptr;
}