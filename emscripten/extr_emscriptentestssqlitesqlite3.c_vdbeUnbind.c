#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ magic; scalar_t__ pc; int nVar; int expmask; int expired; scalar_t__ isPrepareV2; TYPE_6__* db; TYPE_2__* aVar; int /*<<< orphan*/  zSql; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Null ; 
 int SQLITE_MISUSE ; 
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_RANGE ; 
 scalar_t__ VDBE_MAGIC_RUN ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_log (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ vdbeSafetyNotNull (TYPE_1__*) ; 

__attribute__((used)) static int vdbeUnbind(Vdbe *p, int i){
  Mem *pVar;
  if( vdbeSafetyNotNull(p) ){
    return SQLITE_MISUSE_BKPT;
  }
  sqlite3_mutex_enter(p->db->mutex);
  if( p->magic!=VDBE_MAGIC_RUN || p->pc>=0 ){
    sqlite3Error(p->db, SQLITE_MISUSE, 0);
    sqlite3_mutex_leave(p->db->mutex);
    sqlite3_log(SQLITE_MISUSE, 
        "bind on a busy prepared statement: [%s]", p->zSql);
    return SQLITE_MISUSE_BKPT;
  }
  if( i<1 || i>p->nVar ){
    sqlite3Error(p->db, SQLITE_RANGE, 0);
    sqlite3_mutex_leave(p->db->mutex);
    return SQLITE_RANGE;
  }
  i--;
  pVar = &p->aVar[i];
  sqlite3VdbeMemRelease(pVar);
  pVar->flags = MEM_Null;
  sqlite3Error(p->db, SQLITE_OK, 0);

  /* If the bit corresponding to this variable in Vdbe.expmask is set, then 
  ** binding a new value to this variable invalidates the current query plan.
  **
  ** IMPLEMENTATION-OF: R-48440-37595 If the specific value bound to host
  ** parameter in the WHERE clause might influence the choice of query plan
  ** for a statement, then the statement will be automatically recompiled,
  ** as if there had been a schema change, on the first sqlite3_step() call
  ** following any change to the bindings of that parameter.
  */
  if( p->isPrepareV2 &&
     ((i<32 && p->expmask & ((u32)1 << i)) || p->expmask==0xffffffff)
  ){
    p->expired = 1;
  }
  return SQLITE_OK;
}