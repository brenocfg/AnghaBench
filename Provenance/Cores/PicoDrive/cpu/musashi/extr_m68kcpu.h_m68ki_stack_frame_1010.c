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
typedef  int uint ;

/* Variables and functions */
 int /*<<< orphan*/  m68ki_push_16 (int) ; 
 int /*<<< orphan*/  m68ki_push_32 (int) ; 

void m68ki_stack_frame_1010(uint sr, uint vector, uint pc)
{
	/* INTERNAL REGISTER */
	m68ki_push_16(0);

	/* INTERNAL REGISTER */
	m68ki_push_16(0);

	/* DATA OUTPUT BUFFER (2 words) */
	m68ki_push_32(0);

	/* INTERNAL REGISTER */
	m68ki_push_16(0);

	/* INTERNAL REGISTER */
	m68ki_push_16(0);

	/* DATA CYCLE FAULT ADDRESS (2 words) */
	m68ki_push_32(0);

	/* INSTRUCTION PIPE STAGE B */
	m68ki_push_16(0);

	/* INSTRUCTION PIPE STAGE C */
	m68ki_push_16(0);

	/* SPECIAL STATUS REGISTER */
	m68ki_push_16(0);

	/* INTERNAL REGISTER */
	m68ki_push_16(0);

	/* 1010, VECTOR OFFSET */
	m68ki_push_16(0xa000 | (vector<<2));

	/* PROGRAM COUNTER */
	m68ki_push_32(pc);

	/* STATUS REGISTER */
	m68ki_push_16(sr);
}