#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyParser ;
struct TYPE_5__ {int /*<<< orphan*/  b; } ;
struct TYPE_6__ {TYPE_1__ yy90; int /*<<< orphan*/  yy203; int /*<<< orphan*/  yy384; int /*<<< orphan*/  yy451; int /*<<< orphan*/  yy259; int /*<<< orphan*/  yy322; int /*<<< orphan*/  yy314; int /*<<< orphan*/  yy387; } ;
typedef  TYPE_2__ YYMINORTYPE ;
typedef  int YYCODETYPE ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 TYPE_4__* pParse ; 
 int /*<<< orphan*/  sqlite3DeleteTriggerStep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ParserARG_FETCH ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WithDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

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
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 163: /* select */
    case 195: /* selectnowith */
    case 196: /* oneselect */
    case 207: /* values */
{
sqlite3SelectDelete(pParse->db, (yypminor->yy387));
}
      break;
    case 173: /* term */
    case 174: /* expr */
    case 202: /* where_opt */
    case 204: /* having_opt */
    case 216: /* on_opt */
    case 227: /* case_operand */
    case 229: /* case_else */
    case 238: /* when_clause */
    case 243: /* key_opt */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy314));
}
      break;
    case 178: /* eidlist_opt */
    case 187: /* sortlist */
    case 188: /* eidlist */
    case 200: /* selcollist */
    case 203: /* groupby_opt */
    case 205: /* orderby_opt */
    case 208: /* nexprlist */
    case 209: /* exprlist */
    case 210: /* sclp */
    case 220: /* setlist */
    case 226: /* paren_exprlist */
    case 228: /* case_exprlist */
{
sqlite3ExprListDelete(pParse->db, (yypminor->yy322));
}
      break;
    case 194: /* fullname */
    case 201: /* from */
    case 212: /* seltablist */
    case 213: /* stl_prefix */
{
sqlite3SrcListDelete(pParse->db, (yypminor->yy259));
}
      break;
    case 197: /* wqlist */
{
sqlite3WithDelete(pParse->db, (yypminor->yy451));
}
      break;
    case 217: /* using_opt */
    case 218: /* idlist */
    case 222: /* idlist_opt */
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
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}