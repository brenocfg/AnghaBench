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
 int /*<<< orphan*/  emith_move_r_imm (int,int) ; 
 int* hostreg_r ; 

__attribute__((used)) static void tr_mov16(int r, int val)
{
	if (hostreg_r[r] != val) {
		emith_move_r_imm(r, val);
		hostreg_r[r] = val;
	}
}