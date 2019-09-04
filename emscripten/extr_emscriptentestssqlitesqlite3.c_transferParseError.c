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
struct TYPE_4__ {scalar_t__ zErrMsg; scalar_t__ nErr; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void transferParseError(Parse *pTo, Parse *pFrom){
  assert( pFrom->zErrMsg==0 || pFrom->nErr );
  assert( pTo->zErrMsg==0 || pTo->nErr );
  if( pTo->nErr==0 ){
    pTo->zErrMsg = pFrom->zErrMsg;
    pTo->nErr = pFrom->nErr;
  }else{
    sqlite3DbFree(pFrom->db, pFrom->zErrMsg);
  }
}