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
 int /*<<< orphan*/  EOP_ADD_IMM (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  EOP_LDRH_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SSP_XST ; 

__attribute__((used)) static void tr_XST_to_r0(int op)
{
	EOP_ADD_IMM(0, 7, 24/2, 4);	// add r0, r7, #0x400
	EOP_LDRH_IMM(0, 0, SSP_XST*4+2);
}