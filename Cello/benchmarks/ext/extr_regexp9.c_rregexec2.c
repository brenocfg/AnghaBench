#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** reliste; int /*<<< orphan*/ ** relist; } ;
typedef  int /*<<< orphan*/  Rune ;
typedef  int /*<<< orphan*/  Resub ;
typedef  int /*<<< orphan*/  Reprog ;
typedef  TYPE_1__ Reljunk ;
typedef  int /*<<< orphan*/  Relist ;

/* Variables and functions */
 int LISTSIZE ; 
 int nelem (int /*<<< orphan*/ *) ; 
 int rregexec1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int
rregexec2(const Reprog *progp,	/* program to run */
	Rune *bol,	/* string to run machine on */
	Resub *mp,	/* subexpression elements */
	int ms,		/* number of elements at mp */
	Reljunk *j
)
{
	Relist relist0[5*LISTSIZE], relist1[5*LISTSIZE];

	/* mark space */
	j->relist[0] = relist0;
	j->relist[1] = relist1;
	j->reliste[0] = relist0 + nelem(relist0) - 2;
	j->reliste[1] = relist1 + nelem(relist1) - 2;

	return rregexec1(progp, bol, mp, ms, j);
}