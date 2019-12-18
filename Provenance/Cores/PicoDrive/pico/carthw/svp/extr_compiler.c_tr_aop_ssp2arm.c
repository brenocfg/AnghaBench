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
 int A_OP_ADD ; 
 int A_OP_AND ; 
 int A_OP_CMP ; 
 int A_OP_EOR ; 
 int A_OP_ORR ; 
 int A_OP_SUB ; 
 int /*<<< orphan*/  tr_unhandled () ; 

__attribute__((used)) static int tr_aop_ssp2arm(int op)
{
	switch (op) {
		case 1: return A_OP_SUB;
		case 3: return A_OP_CMP;
		case 4: return A_OP_ADD;
		case 5: return A_OP_AND;
		case 6: return A_OP_ORR;
		case 7: return A_OP_EOR;
	}

	tr_unhandled();
	return 0;
}