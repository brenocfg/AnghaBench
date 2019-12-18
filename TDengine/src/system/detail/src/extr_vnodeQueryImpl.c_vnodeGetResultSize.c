#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_size; } ;
typedef  int int32_t ;
struct TYPE_7__ {int rowSize; TYPE_1__** sdata; } ;
struct TYPE_8__ {TYPE_2__ query; int /*<<< orphan*/ * pMeterQuerySupporter; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SQInfo ;

/* Variables and functions */
 int /*<<< orphan*/  dError (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isTSCompQuery (TYPE_2__*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int32_t vnodeGetResultSize(void *thandle, int32_t *numOfRows) {
  SQInfo *pQInfo = (SQInfo *)thandle;
  SQuery *pQuery = &pQInfo->query;

  /*
   * get the file size and set the numOfRows to be the file size, since for tsComp query,
   * the returned row size is equalled to 1
   *
   * TODO handle the case that the file is too large to send back one time
   */
  if (pQInfo->pMeterQuerySupporter != NULL && isTSCompQuery(pQuery) && (*numOfRows) > 0) {
    struct stat fstat;
    if (stat(pQuery->sdata[0]->data, &fstat) == 0) {
      *numOfRows = fstat.st_size;
      return fstat.st_size;
    } else {
      dError("QInfo:%p failed to get file info, path:%s, reason:%s", pQInfo, pQuery->sdata[0]->data, strerror(errno));
      return 0;
    }
  } else {
    return pQInfo->query.rowSize * (*numOfRows);
  }
}