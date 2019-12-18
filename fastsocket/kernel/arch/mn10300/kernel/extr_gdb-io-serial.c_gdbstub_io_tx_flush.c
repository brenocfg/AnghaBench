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
 int /*<<< orphan*/  DTR ; 
 int /*<<< orphan*/  FLOWCTL_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSR_WAIT_FOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEMT ; 
 int /*<<< orphan*/  THRE ; 

void gdbstub_io_tx_flush(void)
{
	LSR_WAIT_FOR(TEMT);
	LSR_WAIT_FOR(THRE);
	FLOWCTL_CLEAR(DTR);
}