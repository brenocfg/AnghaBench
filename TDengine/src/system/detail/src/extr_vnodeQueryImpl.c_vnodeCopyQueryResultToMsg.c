#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {scalar_t__ numOfOutputCols; TYPE_1__** sdata; int /*<<< orphan*/ * pSelectExpr; } ;
struct TYPE_10__ {TYPE_2__ query; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SQInfo ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ VALIDFD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dError (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doCopyQueryResultToMsg (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isTSCompQuery (TYPE_2__*) ; 
 size_t lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int32_t vnodeCopyQueryResultToMsg(void *handle, char *data, int32_t numOfRows, int32_t* size) {
  SQInfo *pQInfo = (SQInfo *)handle;
  SQuery *   pQuery = &pQInfo->query;

  assert(pQuery->pSelectExpr != NULL && pQuery->numOfOutputCols > 0);

  // load data from file to msg buffer
  if (isTSCompQuery(pQuery)) {
    int32_t fd = open(pQuery->sdata[0]->data, O_RDONLY, 0666);

    // make sure file exist
    if (VALIDFD(fd)) {
      size_t s = lseek(fd, 0, SEEK_END);
      dTrace("QInfo:%p ts comp data return, file:%s, size:%ld", pQInfo, pQuery->sdata[0]->data, size);

      lseek(fd, 0, SEEK_SET);
      read(fd, data, s);
      close(fd);

      unlink(pQuery->sdata[0]->data);
    } else {
      dError("QInfo:%p failed to open tmp file to send ts-comp data to client, path:%s, reason:%s", pQInfo,
             pQuery->sdata[0]->data, strerror(errno));
    }
  } else {
    doCopyQueryResultToMsg(pQInfo, numOfRows, data, size);
  }

  return numOfRows;
}