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
 int /*<<< orphan*/  EOP_MOV_REG_LSR (int /*<<< orphan*/ ,int,int) ; 
 int* hostreg_r ; 
 int /*<<< orphan*/  tr_flush_dirty_P () ; 

__attribute__((used)) static void tr_P_to_r0(int op)
{
	tr_flush_dirty_P();
	EOP_MOV_REG_LSR(0, 10, 16);		// mov  r0, r10, lsr #16
	hostreg_r[0] = -1;
}