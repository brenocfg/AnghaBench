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
struct TYPE_2__ {scalar_t__ isMutexInit; scalar_t__ isMallocInit; scalar_t__ isPCacheInit; scalar_t__ isInit; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 TYPE_1__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3MallocEnd () ; 
 int /*<<< orphan*/  sqlite3MutexEnd () ; 
 int /*<<< orphan*/  sqlite3PcacheShutdown () ; 
 int /*<<< orphan*/  sqlite3_os_end () ; 
 int /*<<< orphan*/  sqlite3_reset_auto_extension () ; 

int sqlite3_shutdown(void){
  if( sqlite3GlobalConfig.isInit ){
    sqlite3_os_end();
    sqlite3_reset_auto_extension();
    sqlite3GlobalConfig.isInit = 0;
  }
  if( sqlite3GlobalConfig.isPCacheInit ){
    sqlite3PcacheShutdown();
    sqlite3GlobalConfig.isPCacheInit = 0;
  }
  if( sqlite3GlobalConfig.isMallocInit ){
    sqlite3MallocEnd();
    sqlite3GlobalConfig.isMallocInit = 0;
  }
  if( sqlite3GlobalConfig.isMutexInit ){
    sqlite3MutexEnd();
    sqlite3GlobalConfig.isMutexInit = 0;
  }

  return SQLITE_OK;
}