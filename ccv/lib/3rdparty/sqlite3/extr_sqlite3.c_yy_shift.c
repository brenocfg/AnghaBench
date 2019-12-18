#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  yy0; } ;
struct TYPE_9__ {TYPE_1__ minor; scalar_t__ major; scalar_t__ stateno; } ;
typedef  TYPE_2__ yyStackEntry ;
struct TYPE_10__ {int yyhwm; size_t yystksz; TYPE_2__* yytos; TYPE_2__* yystack; TYPE_2__* yystackEnd; } ;
typedef  TYPE_3__ yyParser ;
typedef  int /*<<< orphan*/  sqlite3ParserTOKENTYPE ;
typedef  scalar_t__ YYCODETYPE ;
typedef  scalar_t__ YYACTIONTYPE ;

/* Variables and functions */
 int YY_MAX_SHIFT ; 
 scalar_t__ YY_MIN_REDUCE ; 
 scalar_t__ YY_MIN_SHIFTREDUCE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ yyGrowStack (TYPE_3__*) ; 
 int /*<<< orphan*/  yyStackOverflow (TYPE_3__*) ; 
 int /*<<< orphan*/  yyTraceShift (TYPE_3__*,int,char*) ; 

__attribute__((used)) static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  sqlite3ParserTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}