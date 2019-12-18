#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * Tree ;
struct TYPE_15__ {scalar_t__ points; } ;
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  file; } ;
struct TYPE_11__ {TYPE_3__ src; int /*<<< orphan*/  point; } ;
struct TYPE_12__ {TYPE_1__ point; } ;
struct TYPE_14__ {TYPE_2__ u; } ;
typedef  TYPE_3__ Coordinate ;
typedef  TYPE_4__* Code ;

/* Variables and functions */
 int /*<<< orphan*/  Defpoint ; 
 int /*<<< orphan*/  Gen ; 
 int /*<<< orphan*/  apply (scalar_t__,TYPE_3__*,int /*<<< orphan*/ **) ; 
 TYPE_4__* code (int /*<<< orphan*/ ) ; 
 TYPE_7__ events ; 
 int findcount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int glevel ; 
 int /*<<< orphan*/  identifiers ; 
 int /*<<< orphan*/  listnodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locus (int /*<<< orphan*/ ,TYPE_3__*) ; 
 float ncalled ; 
 int /*<<< orphan*/  npoints ; 
 scalar_t__ reachable (int /*<<< orphan*/ ) ; 
 float refinc ; 
 TYPE_3__ src ; 

void definept(Coordinate *p) {
	Code cp = code(Defpoint);

	cp->u.point.src = p ? *p : src;
	cp->u.point.point = npoints;
	if (ncalled > 0) {
		int n = findcount(cp->u.point.src.file,
			cp->u.point.src.x, cp->u.point.src.y);
		if (n > 0)
			refinc = (float)n/ncalled;
	}
	if (glevel > 2)	locus(identifiers, &cp->u.point.src);
	if (events.points && reachable(Gen))
		{
			Tree e = NULL;
			apply(events.points, &cp->u.point.src, &e);
			if (e)
				listnodes(e, 0, 0);
		}
}