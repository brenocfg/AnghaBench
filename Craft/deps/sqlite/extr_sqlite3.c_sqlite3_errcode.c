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
struct TYPE_4__ {int errCode; int errMask; scalar_t__ mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_NOMEM ; 
 int /*<<< orphan*/  sqlite3SafetyCheckSickOrOk (TYPE_1__*) ; 

int sqlite3_errcode(sqlite3 *db){
  if( db && !sqlite3SafetyCheckSickOrOk(db) ){
    return SQLITE_MISUSE_BKPT;
  }
  if( !db || db->mallocFailed ){
    return SQLITE_NOMEM;
  }
  return db->errCode & db->errMask;
}