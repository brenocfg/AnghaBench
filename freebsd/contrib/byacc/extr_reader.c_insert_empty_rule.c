#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ args; int /*<<< orphan*/  class; int /*<<< orphan*/  tag; struct TYPE_6__* next; } ;
typedef  TYPE_1__ bucket ;
typedef  scalar_t__ Value_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION ; 
 scalar_t__ CACHE_SIZE ; 
 int /*<<< orphan*/  TOKEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int cache ; 
 scalar_t__ cache_size ; 
 int /*<<< orphan*/  expand_items () ; 
 int /*<<< orphan*/  expand_rules () ; 
 int gensym ; 
 TYPE_1__* last_symbol ; 
 TYPE_1__* make_bucket (int) ; 
 scalar_t__ maxitems ; 
 size_t maxrules ; 
 scalar_t__ nitems ; 
 size_t nrules ; 
 TYPE_1__** pitem ; 
 TYPE_1__** plhs ; 
 int /*<<< orphan*/ * rassoc ; 
 scalar_t__* rprec ; 
 int /*<<< orphan*/  sprintf (int,char*,int) ; 

__attribute__((used)) static void
insert_empty_rule(void)
{
    bucket *bp, **bpp;

    assert(cache);
    assert(cache_size >= CACHE_SIZE);
    sprintf(cache, "$$%d", ++gensym);
    bp = make_bucket(cache);
    last_symbol->next = bp;
    last_symbol = bp;
    bp->tag = plhs[nrules]->tag;
    bp->class = ACTION;
#if defined(YYBTYACC)
    bp->args = 0;
#endif

    nitems = (Value_t)(nitems + 2);
    if (nitems > maxitems)
	expand_items();
    bpp = pitem + nitems - 1;
    *bpp-- = bp;
    while ((bpp[0] = bpp[-1]) != 0)
	--bpp;

    if (++nrules >= maxrules)
	expand_rules();
    plhs[nrules] = plhs[nrules - 1];
    plhs[nrules - 1] = bp;
    rprec[nrules] = rprec[nrules - 1];
    rprec[nrules - 1] = 0;
    rassoc[nrules] = rassoc[nrules - 1];
    rassoc[nrules - 1] = TOKEN;
}