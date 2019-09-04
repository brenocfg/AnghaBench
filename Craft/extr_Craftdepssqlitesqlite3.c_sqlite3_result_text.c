#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* db; } ;
struct TYPE_8__ {TYPE_2__ s; } ;
typedef  TYPE_3__ sqlite3_context ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setResultStrOrError (TYPE_3__*,char const*,int,int /*<<< orphan*/ ,void (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3_result_text(
  sqlite3_context *pCtx, 
  const char *z, 
  int n,
  void (*xDel)(void *)
){
  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
  setResultStrOrError(pCtx, z, n, SQLITE_UTF8, xDel);
}