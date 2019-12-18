#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSQLExprList ;
struct TYPE_8__ {scalar_t__ nType; int i64Key; double dKey; } ;
struct TYPE_9__ {scalar_t__ nSQLOptr; struct TYPE_9__* pRight; struct TYPE_9__* pLeft; int /*<<< orphan*/ * pParam; TYPE_1__ val; } ;
typedef  TYPE_2__ tSQLExpr ;
typedef  double int64_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  TK_DIVIDE 132 
 void* TK_FLOAT ; 
 int TK_IN ; 
 scalar_t__ TK_INTEGER ; 
#define  TK_MINUS 131 
#define  TK_PLUS 130 
#define  TK_REM 129 
 int TK_SET ; 
#define  TK_STAR 128 
 scalar_t__ TK_TIMESTAMP ; 
 scalar_t__ TSDB_DATA_TYPE_BIGINT ; 
 scalar_t__ TSDB_DATA_TYPE_DOUBLE ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  tSQLExprDestroy (TYPE_2__*) ; 

tSQLExpr *tSQLExprCreate(tSQLExpr *pLeft, tSQLExpr *pRight, int32_t optrType) {
  tSQLExpr *pExpr = calloc(1, sizeof(tSQLExpr));

  if (optrType == TK_PLUS || optrType == TK_MINUS || optrType == TK_STAR || optrType == TK_DIVIDE ||
      optrType == TK_REM) {
    /*
     * if a token is noted as the TK_TIMESTAMP, the time precision is microsecond
     * Otherwise, the time precision is adaptive, determined by the time precision from databases.
     */
    if ((pLeft->nSQLOptr == TK_INTEGER && pRight->nSQLOptr == TK_INTEGER) ||
        (pLeft->nSQLOptr == TK_TIMESTAMP && pRight->nSQLOptr == TK_TIMESTAMP)) {
      pExpr->val.nType = TSDB_DATA_TYPE_BIGINT;
      pExpr->nSQLOptr = pLeft->nSQLOptr;

      switch (optrType) {
        case TK_PLUS: {
          pExpr->val.i64Key = pLeft->val.i64Key + pRight->val.i64Key;
          break;
        }
        case TK_MINUS: {
          pExpr->val.i64Key = pLeft->val.i64Key - pRight->val.i64Key;
          break;
        }
        case TK_STAR: {
          pExpr->val.i64Key = pLeft->val.i64Key * pRight->val.i64Key;
          break;
        }
        case TK_DIVIDE: {
          pExpr->nSQLOptr = TK_FLOAT;
          pExpr->val.nType = TSDB_DATA_TYPE_DOUBLE;
          pExpr->val.dKey = (double)pLeft->val.i64Key / pRight->val.i64Key;
          break;
        }
        case TK_REM: {
          pExpr->val.i64Key = pLeft->val.i64Key % pRight->val.i64Key;
          break;
        }
      }

      tSQLExprDestroy(pLeft);
      tSQLExprDestroy(pRight);

    } else if ((pLeft->val.nType == TSDB_DATA_TYPE_DOUBLE && pRight->val.nType == TSDB_DATA_TYPE_BIGINT) ||
               (pRight->val.nType == TSDB_DATA_TYPE_DOUBLE && pLeft->val.nType == TSDB_DATA_TYPE_BIGINT)) {
      pExpr->val.nType = TSDB_DATA_TYPE_DOUBLE;
      pExpr->nSQLOptr = TK_FLOAT;

      double left = pLeft->val.nType == TSDB_DATA_TYPE_DOUBLE ? pLeft->val.dKey : pLeft->val.i64Key;
      double right = pRight->val.nType == TSDB_DATA_TYPE_DOUBLE ? pRight->val.dKey : pRight->val.i64Key;

      switch (optrType) {
        case TK_PLUS: {
          pExpr->val.dKey = left + right;
          break;
        }
        case TK_MINUS: {
          pExpr->val.dKey = left - right;
          break;
        }
        case TK_STAR: {
          pExpr->val.dKey = left * right;
          break;
        }
        case TK_DIVIDE: {
          pExpr->val.dKey = left / right;
          break;
        }
        case TK_REM: {
          pExpr->val.dKey = left - ((int64_t)(left / right)) * right;
          break;
        }
      }

      tSQLExprDestroy(pLeft);
      tSQLExprDestroy(pRight);

    } else {
      pExpr->nSQLOptr = optrType;
      pExpr->pLeft = pLeft;
      pExpr->pRight = pRight;
    }
  } else if (optrType == TK_IN) {
    pExpr->nSQLOptr = optrType;
    pExpr->pLeft = pLeft;

    tSQLExpr *pRSub = calloc(1, sizeof(tSQLExpr));
    pRSub->nSQLOptr = TK_SET;  // TODO refactor .....
    pRSub->pParam = (tSQLExprList *)pRight;

    pExpr->pRight = pRSub;
  } else {
    pExpr->nSQLOptr = optrType;
    pExpr->pLeft = pLeft;
    pExpr->pRight = pRight;
  }

  return pExpr;
}