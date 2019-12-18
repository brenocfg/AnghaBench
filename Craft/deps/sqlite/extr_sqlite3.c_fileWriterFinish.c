#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  size_t i64 ;
struct TYPE_4__ {int eFWErr; size_t iBufEnd; size_t iBufStart; size_t iWriteOff; int /*<<< orphan*/ * aBuffer; int /*<<< orphan*/  pFile; } ;
typedef  TYPE_1__ FileWriter ;

/* Variables and functions */
 scalar_t__ ALWAYS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int fileWriterFinish(sqlite3 *db, FileWriter *p, i64 *piEof){
  int rc;
  if( p->eFWErr==0 && ALWAYS(p->aBuffer) && p->iBufEnd>p->iBufStart ){
    p->eFWErr = sqlite3OsWrite(p->pFile, 
        &p->aBuffer[p->iBufStart], p->iBufEnd - p->iBufStart, 
        p->iWriteOff + p->iBufStart
    );
  }
  *piEof = (p->iWriteOff + p->iBufEnd);
  sqlite3DbFree(db, p->aBuffer);
  rc = p->eFWErr;
  memset(p, 0, sizeof(FileWriter));
  return rc;
}