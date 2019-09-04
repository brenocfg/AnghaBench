#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyParser ;
struct TYPE_5__ {int /*<<< orphan*/ * z; } ;
struct TYPE_4__ {TYPE_3__ yy0; } ;
typedef  TYPE_1__ YYMINORTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pParse ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ParserARG_FETCH ; 
 int /*<<< orphan*/  sqlite3ParserARG_STORE ; 

__attribute__((used)) static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  sqlite3ParserARG_FETCH;
#define TOKEN (yyminor.yy0)

  UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  assert( TOKEN.z[0] );  /* The tokenizer always gives us a token */
  sqlite3ErrorMsg(pParse, "near \"%T\": syntax error", &TOKEN);
  sqlite3ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}