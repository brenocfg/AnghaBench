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
struct TYPE_2__ {scalar_t__ nExt; scalar_t__ aExt; } ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 scalar_t__ sqlite3_initialize () ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 TYPE_1__ wsdAutoext ; 
 int /*<<< orphan*/  wsdAutoextInit ; 

void sqlite3_reset_auto_extension(void){
#ifndef SQLITE_OMIT_AUTOINIT
  if( sqlite3_initialize()==SQLITE_OK )
#endif
  {
#if SQLITE_THREADSAFE
    sqlite3_mutex *mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER);
#endif
    wsdAutoextInit;
    sqlite3_mutex_enter(mutex);
    sqlite3_free(wsdAutoext.aExt);
    wsdAutoext.aExt = 0;
    wsdAutoext.nExt = 0;
    sqlite3_mutex_leave(mutex);
  }
}