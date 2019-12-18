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
 int /*<<< orphan*/  EOP_AND_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_MOV_REG_LSR (int /*<<< orphan*/ ,int,int) ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_ST_to_r0(int op)
{
	// VR doesn't need much accuracy here..
	EOP_MOV_REG_LSR(0, 6, 4);		// mov  r0, r6, lsr #4
	EOP_AND_IMM(0, 0, 0, 0x67);		// and  r0, r0, #0x67
	hostreg_r[0] = -1;
}