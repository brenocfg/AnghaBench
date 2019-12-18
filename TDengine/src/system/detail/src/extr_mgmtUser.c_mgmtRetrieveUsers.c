#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int* offset; int* bytes; int numOfReads; void* pNode; } ;
struct TYPE_4__ {char* user; int /*<<< orphan*/  createdTime; scalar_t__ writeAuth; scalar_t__ superAuth; scalar_t__ next; } ;
typedef  TYPE_1__ SUserObj ;
typedef  TYPE_2__ SShowObj ;
typedef  int /*<<< orphan*/  SConnObj ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int mgmtRetrieveUsers(SShowObj *pShow, char *data, int rows, SConnObj *pConn) {
  int       numOfRows = 0;
  SUserObj *pUser = NULL;
  char *    pWrite;
  int       cols = 0;

  while (numOfRows < rows) {
    //    pShow->pNode = sdbFetchRow(userSdb, pShow->pNode, (void **)&pUser);
    pUser = (SUserObj *)pShow->pNode;
    if (pUser == NULL) break;
    pShow->pNode = (void *)pUser->next;

    cols = 0;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, pUser->user);
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    if (pUser->superAuth) {
      strcpy(pWrite, "super");
    } else if (pUser->writeAuth) {
      strcpy(pWrite, "write");
    } else {
      strcpy(pWrite, "read");
    }
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int64_t *)pWrite = pUser->createdTime;
    cols++;

    numOfRows++;
  }
  pShow->numOfReads += numOfRows;
  return numOfRows;
}