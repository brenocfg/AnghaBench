#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spi_transaction_t ;
struct TYPE_2__ {size_t used_transaction_count; int /*<<< orphan*/ * transactions; } ;

/* Variables and functions */
 size_t SDSPI_TRANSACTION_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* s_slots ; 

__attribute__((used)) static spi_transaction_t* get_transaction(int slot)
{
    size_t used_transaction_count = s_slots[slot].used_transaction_count;
    assert(used_transaction_count < SDSPI_TRANSACTION_COUNT);
    spi_transaction_t* ret = &s_slots[slot].transactions[used_transaction_count];
    ++s_slots[slot].used_transaction_count;
    return ret;
}