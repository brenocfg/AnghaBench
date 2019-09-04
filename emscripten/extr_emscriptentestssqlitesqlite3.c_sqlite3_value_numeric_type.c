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
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  applyNumericAffinity (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemStoreType (TYPE_1__*) ; 

int sqlite3_value_numeric_type(sqlite3_value *pVal){
  Mem *pMem = (Mem*)pVal;
  if( pMem->type==SQLITE_TEXT ){
    applyNumericAffinity(pMem);
    sqlite3VdbeMemStoreType(pMem);
  }
  return pMem->type;
}