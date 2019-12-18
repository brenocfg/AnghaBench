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
 int /*<<< orphan*/  m68ki_fake_push_16 () ; 
 int /*<<< orphan*/  m68ki_fake_push_32 () ; 
 int /*<<< orphan*/  m68ki_push_16 (int) ; 
 int /*<<< orphan*/  m68ki_push_32 (int) ; 

void m68ki_stack_frame_1000(uint pc, uint sr, uint vector)
{
	/* VERSION
     * NUMBER
     * INTERNAL INFORMATION, 16 WORDS
     */
	m68ki_fake_push_32();
	m68ki_fake_push_32();
	m68ki_fake_push_32();
	m68ki_fake_push_32();
	m68ki_fake_push_32();
	m68ki_fake_push_32();
	m68ki_fake_push_32();
	m68ki_fake_push_32();

	/* INSTRUCTION INPUT BUFFER */
	m68ki_push_16(0);

	/* UNUSED, RESERVED (not written) */
	m68ki_fake_push_16();

	/* DATA INPUT BUFFER */
	m68ki_push_16(0);

	/* UNUSED, RESERVED (not written) */
	m68ki_fake_push_16();

	/* DATA OUTPUT BUFFER */
	m68ki_push_16(0);

	/* UNUSED, RESERVED (not written) */
	m68ki_fake_push_16();

	/* FAULT ADDRESS */
	m68ki_push_32(0);

	/* SPECIAL STATUS WORD */
	m68ki_push_16(0);

	/* 1000, VECTOR OFFSET */
	m68ki_push_16(0x8000 | (vector<<2));

	/* PROGRAM COUNTER */
	m68ki_push_32(pc);

	/* STATUS REGISTER */
	m68ki_push_16(sr);
}