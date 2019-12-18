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
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* link; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ bucket ;

/* Variables and functions */
 int hash (char const*) ; 
 TYPE_1__* last_symbol ; 
 TYPE_1__* make_bucket (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__** symbol_table ; 

bucket *
lookup(const char *name)
{
    bucket *bp, **bpp;

    bpp = symbol_table + hash(name);
    bp = *bpp;

    while (bp)
    {
	if (strcmp(name, bp->name) == 0)
	    return (bp);
	bpp = &bp->link;
	bp = *bpp;
    }

    *bpp = bp = make_bucket(name);
    last_symbol->next = bp;
    last_symbol = bp;

    return (bp);
}