#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  unmade; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  Dir_MTime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Make_TimeStamp (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int
MakeFindChild(void *gnp, void *pgnp)
{
    GNode          *gn = (GNode *)gnp;
    GNode          *pgn = (GNode *)pgnp;

    (void)Dir_MTime(gn, 0);
    Make_TimeStamp(pgn, gn);
    pgn->unmade--;

    return (0);
}