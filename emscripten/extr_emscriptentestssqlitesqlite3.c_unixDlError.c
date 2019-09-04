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
typedef  int /*<<< orphan*/  sqlite3_vfs ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 char* dlerror () ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 int /*<<< orphan*/  unixEnterMutex () ; 
 int /*<<< orphan*/  unixLeaveMutex () ; 

__attribute__((used)) static void unixDlError(sqlite3_vfs *NotUsed, int nBuf, char *zBufOut){
  const char *zErr;
  UNUSED_PARAMETER(NotUsed);
  unixEnterMutex();
  zErr = dlerror();
  if( zErr ){
    sqlite3_snprintf(nBuf, zBufOut, "%s", zErr);
  }
  unixLeaveMutex();
}