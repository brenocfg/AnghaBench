#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  YYSTYPE ;

/* Variables and functions */
 int YYMAXSTACKSIZE ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ yydebug ; 
 int /*<<< orphan*/  yyfree (short*) ; 
 scalar_t__ yyrealloc (char*,int) ; 
 short* yyss ; 
 int yystacksize ; 
 int /*<<< orphan*/ * yyvs ; 

__attribute__((used)) static int
#ifdef __GNUC__
inline
#endif
yygrow ()
{
    int old_stacksize = yystacksize;
    short *new_yyss;
    YYSTYPE *new_yyvs;

    if (yystacksize == YYMAXSTACKSIZE)
        return (1);
    yystacksize += (yystacksize + 1 ) / 2;
    if (yystacksize > YYMAXSTACKSIZE)
        yystacksize = YYMAXSTACKSIZE;
#if YYDEBUG
    if (yydebug)
        printf("yydebug: growing stack size from %d to %d\n",
               old_stacksize, yystacksize);
#endif
    new_yyss = (short *) yyrealloc ((char *)yyss, yystacksize * sizeof (short));
    if (new_yyss == 0)
        return (1);
    new_yyvs = (YYSTYPE *) yyrealloc ((char *)yyvs, yystacksize * sizeof (YYSTYPE));
    if (new_yyvs == 0)
    {
        yyfree (new_yyss);
        return (1);
    }
    yyss = new_yyss;
    yyvs = new_yyvs;
    return (0);
}