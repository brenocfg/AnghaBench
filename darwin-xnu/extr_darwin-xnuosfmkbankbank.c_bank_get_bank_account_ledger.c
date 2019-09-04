#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ledger_t ;
typedef  TYPE_1__* bank_account_t ;
struct TYPE_4__ {scalar_t__ ba_holder; scalar_t__ ba_merchant; int /*<<< orphan*/  ba_bill; } ;

/* Variables and functions */
 TYPE_1__* BANK_ACCOUNT_NULL ; 
 int /*<<< orphan*/  LEDGER_NULL ; 

__attribute__((used)) static ledger_t
bank_get_bank_account_ledger(bank_account_t bank_account)
{
	ledger_t bankledger = LEDGER_NULL;

	if (bank_account != BANK_ACCOUNT_NULL &&
		bank_account->ba_holder != bank_account->ba_merchant)
		bankledger = bank_account->ba_bill;

	return (bankledger);
}