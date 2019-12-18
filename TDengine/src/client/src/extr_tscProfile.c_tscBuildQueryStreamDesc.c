#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  useconds; int /*<<< orphan*/  queryId; int /*<<< orphan*/  stime; scalar_t__* sql; } ;
struct TYPE_18__ {scalar_t__ numOfQueries; TYPE_9__* qdesc; } ;
struct TYPE_17__ {scalar_t__ interval; int /*<<< orphan*/  slidingTime; int /*<<< orphan*/  ctime; scalar_t__ stime; int /*<<< orphan*/  useconds; int /*<<< orphan*/  num; int /*<<< orphan*/  streamId; scalar_t__* sql; } ;
struct TYPE_16__ {scalar_t__ numOfStreams; TYPE_7__* sdesc; } ;
struct TYPE_11__ {int /*<<< orphan*/  useconds; } ;
struct TYPE_15__ {struct TYPE_15__* next; TYPE_1__ res; int /*<<< orphan*/  queryId; int /*<<< orphan*/  stime; int /*<<< orphan*/ * sqlstr; } ;
struct TYPE_14__ {struct TYPE_14__* next; scalar_t__ interval; int /*<<< orphan*/  slidingTime; int /*<<< orphan*/  ctime; scalar_t__ stime; int /*<<< orphan*/  useconds; int /*<<< orphan*/  num; int /*<<< orphan*/  streamId; TYPE_2__* pSql; } ;
struct TYPE_13__ {TYPE_4__* streamList; TYPE_5__* sqlList; } ;
struct TYPE_12__ {int /*<<< orphan*/ * sqlstr; } ;
typedef  TYPE_3__ STscObj ;
typedef  TYPE_4__ SSqlStream ;
typedef  TYPE_5__ SSqlObj ;
typedef  TYPE_6__ SSList ;
typedef  TYPE_7__ SSDesc ;
typedef  TYPE_8__ SQList ;
typedef  TYPE_9__ SQDesc ;

/* Variables and functions */
 int TSDB_PAYLOAD_SIZE ; 
 int TSDB_SHOW_SQL_LEN ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 

char *tscBuildQueryStreamDesc(char *pMsg, STscObj *pObj) {
  SQList *pQList = (SQList *)pMsg;
  char *  pMax = pMsg + TSDB_PAYLOAD_SIZE - 256;

  SQDesc *pQdesc = pQList->qdesc;
  pQList->numOfQueries = 0;

  // We extract the lock to tscBuildHeartBeatMsg function.
  /* pthread_mutex_lock (&pObj->mutex); */

  pMsg += sizeof(SQList);
  SSqlObj *pSql = pObj->sqlList;
  while (pSql) {
    /*
     * avoid sqlobj may not be correctly removed from sql list
     * e.g., forgetting to free the sql result may cause the sql object still in sql list
     */
    if (pSql->sqlstr == NULL) {
      pSql = pSql->next;
      continue;
    }

    strncpy(pQdesc->sql, pSql->sqlstr, TSDB_SHOW_SQL_LEN - 1);
    pQdesc->sql[TSDB_SHOW_SQL_LEN - 1] = 0;
    pQdesc->stime = pSql->stime;
    pQdesc->queryId = pSql->queryId;
    pQdesc->useconds = pSql->res.useconds;

    pQList->numOfQueries++;
    pQdesc++;
    pSql = pSql->next;
    pMsg += sizeof(SQDesc);
    if (pMsg > pMax) break;
  }

  SSList *pSList = (SSList *)pMsg;
  SSDesc *pSdesc = pSList->sdesc;
  pSList->numOfStreams = 0;

  pMsg += sizeof(SSList);
  SSqlStream *pStream = pObj->streamList;
  while (pStream) {
    strncpy(pSdesc->sql, pStream->pSql->sqlstr, TSDB_SHOW_SQL_LEN - 1);
    pSdesc->sql[TSDB_SHOW_SQL_LEN - 1] = 0;
    pSdesc->streamId = pStream->streamId;
    pSdesc->num = pStream->num;

    pSdesc->useconds = pStream->useconds;
    pSdesc->stime = pStream->stime - pStream->interval;
    pSdesc->ctime = pStream->ctime;

    pSdesc->slidingTime = pStream->slidingTime;
    pSdesc->interval = pStream->interval;

    pSList->numOfStreams++;
    pSdesc++;
    pStream = pStream->next;
    pMsg += sizeof(SSDesc);
    if (pMsg > pMax) break;
  }

  /* pthread_mutex_unlock (&pObj->mutex); */

  return pMsg;
}