#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  minor; scalar_t__ major; scalar_t__ stateno; } ;
typedef  TYPE_1__ yyStackEntry ;
struct TYPE_8__ {scalar_t__ yyidx; scalar_t__ yyidxMax; scalar_t__ yystksz; TYPE_1__* yystack; } ;
typedef  TYPE_2__ yyParser ;
typedef  int /*<<< orphan*/  YYMINORTYPE ;
typedef  scalar_t__ YYCODETYPE ;
typedef  scalar_t__ YYACTIONTYPE ;

/* Variables and functions */
 scalar_t__ YYSTACKDEPTH ; 
 int /*<<< orphan*/  yyGrowStack (TYPE_2__*) ; 
 int /*<<< orphan*/  yyStackOverflow (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyTraceShift (TYPE_2__*,int) ; 

__attribute__((used)) static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
  yyTraceShift(yypParser, yyNewState);
}