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
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_2__ {scalar_t__ alarmThreshold; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 TYPE_1__ mem0 ; 
 int /*<<< orphan*/  softHeapLimitEnforcer ; 
 int /*<<< orphan*/  sqlite3MemoryAlarm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_initialize () ; 
 scalar_t__ sqlite3_memory_used () ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_release_memory (int) ; 

sqlite3_int64 sqlite3_soft_heap_limit64(sqlite3_int64 n){
  sqlite3_int64 priorLimit;
  sqlite3_int64 excess;
#ifndef SQLITE_OMIT_AUTOINIT
  sqlite3_initialize();
#endif
  sqlite3_mutex_enter(mem0.mutex);
  priorLimit = mem0.alarmThreshold;
  sqlite3_mutex_leave(mem0.mutex);
  if( n<0 ) return priorLimit;
  if( n>0 ){
    sqlite3MemoryAlarm(softHeapLimitEnforcer, 0, n);
  }else{
    sqlite3MemoryAlarm(0, 0, 0);
  }
  excess = sqlite3_memory_used() - n;
  if( excess>0 ) sqlite3_release_memory((int)(excess & 0x7fffffff));
  return priorLimit;
}