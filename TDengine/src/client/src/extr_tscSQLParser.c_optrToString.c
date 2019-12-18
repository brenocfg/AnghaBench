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
struct TYPE_3__ {int nSQLOptr; } ;
typedef  TYPE_1__ tSQLExpr ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
#define  TK_DIVIDE 139 
#define  TK_EQ 138 
#define  TK_GE 137 
#define  TK_GT 136 
#define  TK_LE 135 
#define  TK_LIKE 134 
#define  TK_LT 133 
#define  TK_MINUS 132 
#define  TK_NE 131 
#define  TK_PLUS 130 
#define  TK_REM 129 
#define  TK_STAR 128 
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static int32_t optrToString(tSQLExpr* pExpr, char** exprString) {
  const char* le = "<=";
  const char* ge = ">=";
  const char* ne = "<>";
  const char* likeOptr = "LIKE";

  switch (pExpr->nSQLOptr) {
    case TK_LE: {
      *(int16_t*)(*exprString) = *(int16_t*)le;
      *exprString += 1;
      break;
    }
    case TK_GE: {
      *(int16_t*)(*exprString) = *(int16_t*)ge;
      *exprString += 1;
      break;
    }
    case TK_NE: {
      *(int16_t*)(*exprString) = *(int16_t*)ne;
      *exprString += 1;
      break;
    }

    case TK_LT:
      *(*exprString) = '<';
      break;
    case TK_GT:
      *(*exprString) = '>';
      break;
    case TK_EQ:
      *(*exprString) = '=';
      break;
    case TK_PLUS:
      *(*exprString) = '+';
      break;
    case TK_MINUS:
      *(*exprString) = '-';
      break;
    case TK_STAR:
      *(*exprString) = '*';
      break;
    case TK_DIVIDE:
      *(*exprString) = '/';
      break;
    case TK_REM:
      *(*exprString) = '%';
      break;
    case TK_LIKE: {
      int32_t len = sprintf(*exprString, " %s ", likeOptr);
      *exprString += (len - 1);
      break;
    }
    default:
      return TSDB_CODE_INVALID_SQL;
  }

  *exprString += 1;

  return TSDB_CODE_SUCCESS;
}