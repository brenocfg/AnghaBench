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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
#define  TK_AND 141 
#define  TK_EQ 140 
#define  TK_GE 139 
#define  TK_GT 138 
#define  TK_LE 137 
#define  TK_LIKE 136 
#define  TK_LT 135 
#define  TK_MINUS 134 
#define  TK_NE 133 
#define  TK_OR 132 
#define  TK_PLUS 131 
#define  TK_REM 130 
#define  TK_SLASH 129 
#define  TK_STAR 128 
 int /*<<< orphan*/  TSDB_BINARY_OP_ADD ; 
 int /*<<< orphan*/  TSDB_BINARY_OP_DIVIDE ; 
 int /*<<< orphan*/  TSDB_BINARY_OP_MULTIPLY ; 
 int /*<<< orphan*/  TSDB_BINARY_OP_REMAINDER ; 
 int /*<<< orphan*/  TSDB_BINARY_OP_SUBTRACT ; 
 int /*<<< orphan*/  TSDB_RELATION_AND ; 
 int /*<<< orphan*/  TSDB_RELATION_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_LARGE ; 
 int /*<<< orphan*/  TSDB_RELATION_LARGE_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_LESS ; 
 int /*<<< orphan*/  TSDB_RELATION_LESS_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_LIKE ; 
 int /*<<< orphan*/  TSDB_RELATION_NOT_EQUAL ; 
 int /*<<< orphan*/  TSDB_RELATION_OR ; 

__attribute__((used)) static uint8_t getBinaryExprOptr(SSQLToken *pToken) {
  switch (pToken->type) {
    case TK_LT:
      return TSDB_RELATION_LESS;
    case TK_LE:
      return TSDB_RELATION_LESS_EQUAL;
    case TK_GT:
      return TSDB_RELATION_LARGE;
    case TK_GE:
      return TSDB_RELATION_LARGE_EQUAL;
    case TK_NE:
      return TSDB_RELATION_NOT_EQUAL;
    case TK_AND:
      return TSDB_RELATION_AND;
    case TK_OR:
      return TSDB_RELATION_OR;
    case TK_EQ:
      return TSDB_RELATION_EQUAL;
    case TK_PLUS:
      return TSDB_BINARY_OP_ADD;
    case TK_MINUS:
      return TSDB_BINARY_OP_SUBTRACT;
    case TK_STAR:
      return TSDB_BINARY_OP_MULTIPLY;
    case TK_SLASH:
      return TSDB_BINARY_OP_DIVIDE;
    case TK_REM:
      return TSDB_BINARY_OP_REMAINDER;
    case TK_LIKE:
      return TSDB_RELATION_LIKE;
    default: { return 0; }
  }
}