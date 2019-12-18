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
typedef  int /*<<< orphan*/  SAcctObj ;

/* Variables and functions */
 int TSDB_CODE_TOO_MANY_DATABSES ; 
 int /*<<< orphan*/  dbSdb ; 
 int /*<<< orphan*/  mWarn (char*,int,int) ; 
 int sdbGetNumOfRows (int /*<<< orphan*/ ) ; 
 int tsMaxDbs ; 

int mgmtCheckDbLimit(SAcctObj *pAcct) {
  int numOfDbs = sdbGetNumOfRows(dbSdb);
  if (numOfDbs >= tsMaxDbs) {
    mWarn("numOfDbs:%d, exceed tsMaxDbs:%d", numOfDbs, tsMaxDbs);
    return TSDB_CODE_TOO_MANY_DATABSES;
  }
  return 0;
}