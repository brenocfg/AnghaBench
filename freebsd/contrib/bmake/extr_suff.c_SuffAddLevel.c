#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  l; TYPE_2__* s; } ;
struct TYPE_7__ {TYPE_1__* suff; } ;
struct TYPE_6__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_2__ Src ;
typedef  TYPE_3__ LstSrc ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SuffAddSrc ; 

__attribute__((used)) static void
SuffAddLevel(Lst l, Src *targ)
{
    LstSrc         ls;

    ls.s = targ;
    ls.l = l;

    Lst_ForEach(targ->suff->children, SuffAddSrc, &ls);
}