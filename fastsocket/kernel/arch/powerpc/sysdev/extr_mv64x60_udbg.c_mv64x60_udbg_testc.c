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
 int MPSC_INTR_CAUSE_RCC ; 
 int in_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsc_intr_cause ; 

__attribute__((used)) static int mv64x60_udbg_testc(void)
{
	return (in_le32(mpsc_intr_cause) & MPSC_INTR_CAUSE_RCC) != 0;
}