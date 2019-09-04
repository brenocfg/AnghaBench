#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {scalar_t__ nArg; scalar_t__ nUsed; int /*<<< orphan*/ * apArg; } ;
typedef  TYPE_1__ PrintfArguments ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sqlite3_int64 getIntArg(PrintfArguments *p){
  if( p->nArg<=p->nUsed ) return 0;
  return sqlite3_value_int64(p->apArg[p->nUsed++]);
}