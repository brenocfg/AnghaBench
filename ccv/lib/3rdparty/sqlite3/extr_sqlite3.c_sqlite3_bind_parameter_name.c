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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_2__ {int /*<<< orphan*/  pVList; } ;
typedef  TYPE_1__ Vdbe ;

/* Variables and functions */
 char const* sqlite3VListNumToName (int /*<<< orphan*/ ,int) ; 

const char *sqlite3_bind_parameter_name(sqlite3_stmt *pStmt, int i){
  Vdbe *p = (Vdbe*)pStmt;
  if( p==0 ) return 0;
  return sqlite3VListNumToName(p->pVList, i);
}