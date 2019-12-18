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
struct TYPE_3__ {char const nSQLOptr; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  size_t int32_t ;

/* Variables and functions */
 char const TK_IN ; 
 char const TK_LIKE ; 
 size_t tListLen (char const*) ; 

__attribute__((used)) static bool validTableNameOptr(tSQLExpr* pExpr) {
  const char nameFilterOptr[] = {TK_IN, TK_LIKE};

  for (int32_t i = 0; i < tListLen(nameFilterOptr); ++i) {
    if (pExpr->nSQLOptr == nameFilterOptr[i]) {
      return true;
    }
  }

  return false;
}