#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__** a; } ;
struct TYPE_5__ {TYPE_2__* pHash; } ;
struct TYPE_6__ {int /*<<< orphan*/  zName; TYPE_1__ u; } ;
typedef  TYPE_2__ FuncDef ;

/* Variables and functions */
 TYPE_3__ sqlite3BuiltinFunctions ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static FuncDef *functionSearch(
  int h,               /* Hash of the name */
  const char *zFunc    /* Name of function */
){
  FuncDef *p;
  for(p=sqlite3BuiltinFunctions.a[h]; p; p=p->u.pHash){
    if( sqlite3StrICmp(p->zName, zFunc)==0 ){
      return p;
    }
  }
  return 0;
}