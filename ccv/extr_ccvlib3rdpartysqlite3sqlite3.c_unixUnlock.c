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
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int posixUnlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unixUnlock(sqlite3_file *id, int eFileLock){
#if SQLITE_MAX_MMAP_SIZE>0
  assert( eFileLock==SHARED_LOCK || ((unixFile *)id)->nFetchOut==0 );
#endif
  return posixUnlock(id, eFileLock, 0);
}