#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyParser ;
struct TYPE_7__ {int /*<<< orphan*/  b; } ;
struct TYPE_6__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_8__ {TYPE_2__ yy90; int /*<<< orphan*/  yy203; int /*<<< orphan*/  yy384; int /*<<< orphan*/  yy314; int /*<<< orphan*/  yy259; int /*<<< orphan*/  yy322; TYPE_1__ yy118; int /*<<< orphan*/  yy387; } ;
typedef  TYPE_3__ YYMINORTYPE ;
typedef  int YYCODETYPE ;
struct TYPE_9__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 TYPE_5__* pParse ; 
 int /*<<< orphan*/  sqlite3DeleteTriggerStep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ParserARG_FETCH ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  sqlite3ParserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 160: /* select */
    case 194: /* oneselect */
{
sqlite3SelectDelete(pParse->db, (yypminor->yy387));
}
      break;
    case 174: /* term */
    case 175: /* expr */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy118).pExpr);
}
      break;
    case 179: /* idxlist_opt */
    case 187: /* idxlist */
    case 197: /* selcollist */
    case 200: /* groupby_opt */
    case 202: /* orderby_opt */
    case 204: /* sclp */
    case 214: /* sortlist */
    case 216: /* nexprlist */
    case 217: /* setlist */
    case 220: /* itemlist */
    case 221: /* exprlist */
    case 226: /* case_exprlist */
{
sqlite3ExprListDelete(pParse->db, (yypminor->yy322));
}
      break;
    case 193: /* fullname */
    case 198: /* from */
    case 206: /* seltablist */
    case 207: /* stl_prefix */
{
sqlite3SrcListDelete(pParse->db, (yypminor->yy259));
}
      break;
    case 199: /* where_opt */
    case 201: /* having_opt */
    case 210: /* on_opt */
    case 215: /* sortitem */
    case 225: /* case_operand */
    case 227: /* case_else */
    case 238: /* when_clause */
    case 243: /* key_opt */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy314));
}
      break;
    case 211: /* using_opt */
    case 213: /* inscollist */
    case 219: /* inscollist_opt */
{
sqlite3IdListDelete(pParse->db, (yypminor->yy384));
}
      break;
    case 234: /* trigger_cmd_list */
    case 239: /* trigger_cmd */
{
sqlite3DeleteTriggerStep(pParse->db, (yypminor->yy203));
}
      break;
    case 236: /* trigger_event */
{
sqlite3IdListDelete(pParse->db, (yypminor->yy90).b);
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}