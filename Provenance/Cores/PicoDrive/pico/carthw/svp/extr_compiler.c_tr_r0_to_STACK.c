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
 int /*<<< orphan*/  EOP_ADD_IMM (int,int,int,int) ; 
 int /*<<< orphan*/  EOP_ADD_REG_LSR (int,int,int,int) ; 
 int /*<<< orphan*/  EOP_STRH_SIMPLE (int /*<<< orphan*/ ,int) ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_r0_to_STACK(int const_val)
{
	// 448
	EOP_ADD_IMM(1, 7, 24/2, 0x04);		// add  r1, r7, 0x400
	EOP_ADD_IMM(1, 1, 0, 0x48);		// add  r1, r1, 0x048
	EOP_ADD_REG_LSR(1, 1, 6, 28);		// add  r1, r1, r6, lsr #28
	EOP_STRH_SIMPLE(0, 1);			// strh r0, [r1]
	EOP_ADD_IMM(6, 6,  8/2, 0x20);		// add  r6, r6, #1<<29
	hostreg_r[1] = -1;
}