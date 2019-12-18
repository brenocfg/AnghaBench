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
struct TYPE_4__ {scalar_t__ nSQLOptr; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ TK_BINARY ; 
 scalar_t__ TK_BOOL ; 
 scalar_t__ TK_COUNT ; 
 scalar_t__ TK_IN ; 
 scalar_t__ TK_LAST_ROW ; 

__attribute__((used)) static bool isValidExpr(tSQLExpr* pLeft, tSQLExpr* pRight, int32_t optr) {
  if (pLeft == NULL || (pRight == NULL && optr != TK_IN)) {
    return false;
  }

  /*
   * filter illegal expression in where clause:
   * 1. count(*) > 12
   * 2. sum(columnA) > sum(columnB)
   * 3. 4 < 5,  'ABC'>'abc'
   *
   * However, columnA < 4+12 is valid
   */
  if ((pLeft->nSQLOptr >= TK_COUNT && pLeft->nSQLOptr <= TK_LAST_ROW) ||
      (pRight->nSQLOptr >= TK_COUNT && pRight->nSQLOptr <= TK_LAST_ROW) ||
      (pLeft->nSQLOptr >= TK_BOOL && pLeft->nSQLOptr <= TK_BINARY && pRight->nSQLOptr >= TK_BOOL &&
       pRight->nSQLOptr <= TK_BINARY)) {
    return false;
  }

  return true;
}