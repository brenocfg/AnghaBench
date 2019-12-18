#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_uint64 ;
struct TYPE_9__ {TYPE_2__* pOut; } ;
typedef  TYPE_3__ sqlite3_context ;
struct TYPE_8__ {TYPE_1__* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 void SQLITE_DYNAMIC (void*) ; 
 unsigned char SQLITE_UTF16 ; 
 unsigned char SQLITE_UTF16NATIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  invokeValueDestructor (char const*,void (*) (void*),TYPE_3__*) ; 
 int /*<<< orphan*/  setResultStrOrError (TYPE_3__*,char const*,int,unsigned char,void (*) (void*)) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3_result_text64(
  sqlite3_context *pCtx, 
  const char *z, 
  sqlite3_uint64 n,
  void (*xDel)(void *),
  unsigned char enc
){
  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
  assert( xDel!=SQLITE_DYNAMIC );
  if( enc==SQLITE_UTF16 ) enc = SQLITE_UTF16NATIVE;
  if( n>0x7fffffff ){
    (void)invokeValueDestructor(z, xDel, pCtx);
  }else{
    setResultStrOrError(pCtx, z, (int)n, enc, xDel);
  }
}