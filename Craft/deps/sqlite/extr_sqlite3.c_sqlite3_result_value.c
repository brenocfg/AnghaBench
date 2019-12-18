#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_7__ {TYPE_1__* db; } ;
struct TYPE_6__ {TYPE_4__ s; } ;
typedef  TYPE_2__ sqlite3_context ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemCopy (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3_result_value(sqlite3_context *pCtx, sqlite3_value *pValue){
  assert( sqlite3_mutex_held(pCtx->s.db->mutex) );
  sqlite3VdbeMemCopy(&pCtx->s, pValue);
}