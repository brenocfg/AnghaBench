#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  columnMallocFailure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  columnMem (int /*<<< orphan*/ *,int) ; 
 double sqlite3_value_double (int /*<<< orphan*/ ) ; 

double sqlite3_column_double(sqlite3_stmt *pStmt, int i){
  double val = sqlite3_value_double( columnMem(pStmt,i) );
  columnMallocFailure(pStmt);
  return val;
}