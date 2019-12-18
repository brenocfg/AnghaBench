#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ isTransaction; } ;
typedef  TYPE_1__ DistributedExecution ;

/* Variables and functions */
 scalar_t__ XACT_MODIFICATION_DATA ; 
 scalar_t__ XactModificationLevel ; 

__attribute__((used)) static bool
TransactionModifiedDistributedTable(DistributedExecution *execution)
{
	/*
	 * We need to explicitly check for isTransaction due to
	 * citus.function_opens_transaction_block flag. When set to false, we
	 * should not be pretending that we're in a coordinated transaction even
	 * if XACT_MODIFICATION_DATA is set. That's why we implemented this workaround.
	 */
	return execution->isTransaction && XactModificationLevel == XACT_MODIFICATION_DATA;
}