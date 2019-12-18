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
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_5__ {int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_6__ {int validJD; int /*<<< orphan*/  iJD; } ;
typedef  TYPE_2__ DateTime ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ sqlite3OsCurrentTimeInt64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setDateTimeToCurrent(sqlite3_context *context, DateTime *p){
  sqlite3 *db = sqlite3_context_db_handle(context);
  if( sqlite3OsCurrentTimeInt64(db->pVfs, &p->iJD)==SQLITE_OK ){
    p->validJD = 1;
    return 0;
  }else{
    return 1;
  }
}