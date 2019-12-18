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
struct TYPE_3__ {int numOfCols; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  int /*<<< orphan*/  SMgmtHead ;
typedef  int /*<<< orphan*/  SAlterTableMsg ;

/* Variables and functions */
 int TSDB_EXTRA_PAYLOAD_SIZE ; 
 int minMsgSize () ; 

int tscEstimateAlterTableMsgLength(SSqlCmd *pCmd) {
  return minMsgSize() + sizeof(SMgmtHead) + sizeof(SAlterTableMsg) + sizeof(SSchema) * pCmd->numOfCols +
         TSDB_EXTRA_PAYLOAD_SIZE;
}