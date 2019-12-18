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
typedef  int /*<<< orphan*/  YYSTYPE ;
struct TYPE_3__ {unsigned int stacksize; int /*<<< orphan*/ * s_base; int /*<<< orphan*/ * s_last; int /*<<< orphan*/ * p_mark; int /*<<< orphan*/ * p_base; int /*<<< orphan*/ * l_mark; int /*<<< orphan*/ * l_base; int /*<<< orphan*/ * s_mark; } ;
typedef  TYPE_1__ YYSTACKDATA ;
typedef  int /*<<< orphan*/  YYLTYPE ;
typedef  int /*<<< orphan*/  YYINT ;

/* Variables and functions */
 int YYENOMEM ; 
 unsigned int YYINITSTACKSIZE ; 
 unsigned int YYMAXDEPTH ; 
 char* YYPREFIX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ yydebug ; 

__attribute__((used)) static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}