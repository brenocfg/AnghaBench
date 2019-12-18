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
struct TYPE_3__ {int type; scalar_t__ msgType; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_MSG_TYPE_QUERY ; 
 int TSDB_QUERY_TYPE_STABLE_QUERY ; 

bool tscQueryOnMetric(SSqlCmd* pCmd) {
  return ((pCmd->type & TSDB_QUERY_TYPE_STABLE_QUERY) == TSDB_QUERY_TYPE_STABLE_QUERY) &&
         (pCmd->msgType == TSDB_MSG_TYPE_QUERY);
}