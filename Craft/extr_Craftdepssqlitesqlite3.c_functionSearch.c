#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* zName; struct TYPE_6__* pHash; } ;
struct TYPE_5__ {TYPE_2__** a; } ;
typedef  TYPE_1__ FuncDefHash ;
typedef  TYPE_2__ FuncDef ;

/* Variables and functions */
 scalar_t__ sqlite3StrNICmp (scalar_t__*,char const*,int) ; 

__attribute__((used)) static FuncDef *functionSearch(
  FuncDefHash *pHash,  /* Hash table to search */
  int h,               /* Hash of the name */
  const char *zFunc,   /* Name of function */
  int nFunc            /* Number of bytes in zFunc */
){
  FuncDef *p;
  for(p=pHash->a[h]; p; p=p->pHash){
    if( sqlite3StrNICmp(p->zName, zFunc, nFunc)==0 && p->zName[nFunc]==0 ){
      return p;
    }
  }
  return 0;
}