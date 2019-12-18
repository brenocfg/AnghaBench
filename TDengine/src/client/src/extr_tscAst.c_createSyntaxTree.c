#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_21__ {scalar_t__ nodeType; int colId; TYPE_2__* pExpr; } ;
typedef  TYPE_1__ tSQLSyntaxNode ;
struct TYPE_22__ {scalar_t__ nSQLBinaryOptr; TYPE_1__* pRight; TYPE_1__* pLeft; int /*<<< orphan*/  filterOnPrimaryKey; } ;
typedef  TYPE_2__ tSQLBinaryExpr ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_24__ {scalar_t__ n; scalar_t__ type; } ;
struct TYPE_23__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ SSchema ;
typedef  TYPE_4__ SSQLToken ;

/* Variables and functions */
 scalar_t__ TK_AND ; 
 scalar_t__ TK_LP ; 
 scalar_t__ TK_OR ; 
 scalar_t__ TK_RP ; 
 scalar_t__ TSQL_NODE_EXPR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ getBinaryExprOptr (TYPE_4__*) ; 
 int /*<<< orphan*/  isQueryOnPrimaryKey (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  pError (char*,scalar_t__) ; 
 TYPE_1__* parseRemainStr (char*,TYPE_2__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reviseBinaryExprIfNecessary (TYPE_1__**,TYPE_1__**,scalar_t__*) ; 
 TYPE_1__* tSQLSyntaxNodeCreate (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  tSQLSyntaxNodeDestroy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_4__ tStrGetToken (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tSQLSyntaxNode *createSyntaxTree(SSchema *pSchema, int32_t numOfCols, char *str, int32_t *i) {
  SSQLToken t0;

  t0 = tStrGetToken(str, i, false, 0, NULL);
  if (t0.n == 0) {
    return NULL;
  }

  tSQLSyntaxNode *pLeft = NULL;
  if (t0.type == TK_LP) {  // start new left child branch
    pLeft = createSyntaxTree(pSchema, numOfCols, str, i);
  } else {
    if (t0.type == TK_RP) {
      return NULL;
    }
    pLeft = tSQLSyntaxNodeCreate(pSchema, numOfCols, &t0);
  }

  if (pLeft == NULL) {
    return NULL;
  }

  t0 = tStrGetToken(str, i, false, 0, NULL);
  if (t0.n == 0 || t0.type == TK_RP) {
    if (pLeft->nodeType != TSQL_NODE_EXPR) { // if left is not the expr, it is not a legal expr
      tSQLSyntaxNodeDestroy(pLeft, NULL);
      return NULL;
    }

    return pLeft;
  }

  // get the operator of expr
  uint8_t optr = getBinaryExprOptr(&t0);
  if (optr <= 0) {
    pError("not support binary operator:%d", t0.type);
    tSQLSyntaxNodeDestroy(pLeft, NULL);
    return NULL;
  }

  assert(pLeft != NULL);
  tSQLSyntaxNode *pRight = NULL;

  if (t0.type == TK_AND || t0.type == TK_OR || t0.type == TK_LP) {
    pRight = createSyntaxTree(pSchema, numOfCols, str, i);
  } else {
    /*
     * In case that pLeft is a field identification,
     * we parse the value in expression according to queried field type,
     * if we do not get the information, in case of value of field presented first,
     * we revised the value after the binary expression is completed.
     */
    t0 = tStrGetToken(str, i, true, 0, NULL);
    if (t0.n == 0) {
      tSQLSyntaxNodeDestroy(pLeft, NULL);  // illegal expression
      return NULL;
    }

    if (t0.type == TK_LP) {
      pRight = createSyntaxTree(pSchema, numOfCols, str, i);
    } else {
      pRight = tSQLSyntaxNodeCreate(pSchema, numOfCols, &t0);
    }
  }

  if (pRight == NULL) {
    tSQLSyntaxNodeDestroy(pLeft, NULL);
    return NULL;
  }

  /* create binary expr as the child of new parent node */
  tSQLBinaryExpr *pBinExpr = (tSQLBinaryExpr *)calloc(1, sizeof(tSQLBinaryExpr));
  reviseBinaryExprIfNecessary(&pLeft, &pRight, &optr);

  pBinExpr->filterOnPrimaryKey = isQueryOnPrimaryKey(pSchema[0].name, pLeft, pRight);
  pBinExpr->pLeft = pLeft;
  pBinExpr->pRight = pRight;
  pBinExpr->nSQLBinaryOptr = optr;

  t0 = tStrGetToken(str, i, true, 0, NULL);

  if (t0.n == 0 || t0.type == TK_RP) {
    tSQLSyntaxNode *pn = malloc(sizeof(tSQLSyntaxNode));
    pn->nodeType = TSQL_NODE_EXPR;
    pn->pExpr = pBinExpr;
    pn->colId = -1;
    return pn;
  } else {
    uint8_t localOptr = getBinaryExprOptr(&t0);
    if (localOptr <= 0) {
      pError("not support binary operator:%d", t0.type);
      return NULL;
    }

    return parseRemainStr(str, pBinExpr, pSchema, localOptr, numOfCols, i);
  }
}