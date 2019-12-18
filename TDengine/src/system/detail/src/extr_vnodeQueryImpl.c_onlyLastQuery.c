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
typedef  int /*<<< orphan*/  SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_FUNC_LAST ; 
 int /*<<< orphan*/  TSDB_FUNC_LAST_DST ; 
 int onlyOneQueryType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool onlyLastQuery(SQuery *pQuery) { return onlyOneQueryType(pQuery, TSDB_FUNC_LAST, TSDB_FUNC_LAST_DST); }