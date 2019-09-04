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
typedef  int /*<<< orphan*/  ledger_t ;
typedef  int /*<<< orphan*/  ledger_amount_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  ledger_debit_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

kern_return_t
ledger_debit(ledger_t ledger, int entry, ledger_amount_t amount)
{
	return ledger_debit_thread(current_thread(), ledger, entry, amount);
}