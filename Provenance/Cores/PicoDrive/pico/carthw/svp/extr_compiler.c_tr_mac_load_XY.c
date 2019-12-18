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
 int /*<<< orphan*/  EOP_MOV_REG_LSL (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_ORR_REG_SIMPLE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KRREG_P ; 
 int /*<<< orphan*/  KRREG_X ; 
 int /*<<< orphan*/  KRREG_Y ; 
 int /*<<< orphan*/  SSP_X ; 
 int /*<<< orphan*/  SSP_Y ; 
 int /*<<< orphan*/  dirty_regb ; 
 int /*<<< orphan*/  hostreg_sspreg_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  known_regb ; 
 int /*<<< orphan*/  tr_rX_read (int,int) ; 

__attribute__((used)) static void tr_mac_load_XY(int op)
{
	tr_rX_read(op&3, (op>>2)&3); // X
	EOP_MOV_REG_LSL(4, 0, 16);
	tr_rX_read(((op>>4)&3)|4, (op>>6)&3); // Y
	EOP_ORR_REG_SIMPLE(4, 0);
	dirty_regb |= KRREG_P;
	hostreg_sspreg_changed(SSP_X);
	hostreg_sspreg_changed(SSP_Y);
	known_regb &= ~KRREG_X;
	known_regb &= ~KRREG_Y;
}