#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lockingContext; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int /*<<< orphan*/  NO_LOCK ; 
 int SQLITE_OK ; 
 int closeUnixFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dotlockUnlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dotlockClose(sqlite3_file *id) {
  int rc = SQLITE_OK;
  if( id ){
    unixFile *pFile = (unixFile*)id;
    dotlockUnlock(id, NO_LOCK);
    sqlite3_free(pFile->lockingContext);
    rc = closeUnixFile(id);
  }
  return rc;
}