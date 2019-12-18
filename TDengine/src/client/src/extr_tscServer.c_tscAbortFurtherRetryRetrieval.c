#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {TYPE_1__* pState; int /*<<< orphan*/  queryMutex; int /*<<< orphan*/  numOfRetry; } ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_2__ SRetrieveSupport ;
typedef  char* LPVOID ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessage (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_NUM_OF_SUBQUERY_RETRY ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tscError (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tscRetrieveFromVnodeCallBack (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tscAbortFurtherRetryRetrieval(SRetrieveSupport *trsupport, TAOS_RES *tres, int32_t errCode) {
// set no disk space error info
#ifdef WINDOWS
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
                GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Default language
                (LPTSTR)&lpMsgBuf, 0, NULL);
  tscError("sub:%p failed to flush data to disk:reason:%s", tres, lpMsgBuf);
  LocalFree(lpMsgBuf);
#else
  char buf[256] = {0};
  strerror_r(errno, buf, 256);
  tscError("sub:%p failed to flush data to disk:reason:%s", tres, buf);
#endif

  trsupport->pState->code = -errCode;
  trsupport->numOfRetry = MAX_NUM_OF_SUBQUERY_RETRY;

  pthread_mutex_unlock(&trsupport->queryMutex);

  tscRetrieveFromVnodeCallBack(trsupport, tres, trsupport->pState->code);
}