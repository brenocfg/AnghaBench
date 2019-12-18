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
 int /*<<< orphan*/  EOP_MOV_REG_SIMPLE (int /*<<< orphan*/ ,int) ; 
 int SSP_Y ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_Y_to_r0(int op)
{
	if (hostreg_r[0] != (SSP_Y<<16)) {
		EOP_MOV_REG_SIMPLE(0, 4);	// mov  r0, r4
		hostreg_r[0] = SSP_Y<<16;
	}
}