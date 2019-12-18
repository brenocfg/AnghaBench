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
 int SSP_A ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_A_to_r0(int op)
{
	if (hostreg_r[0] != (SSP_A<<16)) {
		EOP_MOV_REG_LSR(0, 5, 16);	// mov  r0, r5, lsr #16  @ AH
		hostreg_r[0] = SSP_A<<16;
	}
}