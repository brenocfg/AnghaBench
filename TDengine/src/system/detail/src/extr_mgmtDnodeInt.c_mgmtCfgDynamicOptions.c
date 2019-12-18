#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int customScore; int bandwidthMb; int /*<<< orphan*/  privateIp; } ;
typedef  TYPE_1__ SDnodeObj ;

/* Variables and functions */
 int TSDB_CODE_INVALID_SQL ; 
 int TSDB_CODE_SUCCESS ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mgmtSetDnodeUnRemove (TYPE_1__*) ; 
 int /*<<< orphan*/  mgmtStartBalanceTimer (int) ; 
 int /*<<< orphan*/  mgmtUpdateDnode (TYPE_1__*) ; 
 int /*<<< orphan*/  paGetToken (char*,char**,int*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  taosIpStr (int /*<<< orphan*/ ) ; 

int mgmtCfgDynamicOptions(SDnodeObj *pDnode, char *msg) {
  char *option, *value;
  int   olen, valen;

  paGetToken(msg, &option, &olen);
  if (strncasecmp(option, "unremove", 8) == 0) {
    mgmtSetDnodeUnRemove(pDnode);
    return TSDB_CODE_SUCCESS;
  } else if (strncasecmp(option, "score", 5) == 0) {
    paGetToken(option + olen + 1, &value, &valen);
    if (valen > 0) {
      int score = atoi(value);
      mTrace("dnode:%s, custom score set from:%d to:%d", taosIpStr(pDnode->privateIp), pDnode->customScore, score);
      pDnode->customScore = score;
      mgmtUpdateDnode(pDnode);
      mgmtStartBalanceTimer(15);
    }
    return TSDB_CODE_INVALID_SQL;
  } else if (strncasecmp(option, "bandwidth", 9) == 0) {
    paGetToken(msg, &value, &valen);
    if (valen > 0) {
      int bandwidthMb = atoi(value);
      if (bandwidthMb >= 0 && bandwidthMb < 10000000) {
        mTrace("dnode:%s, bandwidth(Mb) set from:%d to:%d", taosIpStr(pDnode->privateIp), pDnode->bandwidthMb, bandwidthMb);
        pDnode->bandwidthMb = bandwidthMb;
        mgmtUpdateDnode(pDnode);
        return TSDB_CODE_SUCCESS;
      }
    }
    return TSDB_CODE_INVALID_SQL;
  }

  return -1;
}