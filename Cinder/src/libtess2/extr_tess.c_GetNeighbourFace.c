#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* Rface; } ;
struct TYPE_4__ {int /*<<< orphan*/  n; int /*<<< orphan*/  inside; } ;
typedef  int /*<<< orphan*/  TESSindex ;
typedef  TYPE_2__ TESShalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  TESS_UNDEF ; 

__attribute__((used)) static TESSindex GetNeighbourFace(TESShalfEdge* edge)
{
	if (!edge->Rface)
		return TESS_UNDEF;
	if (!edge->Rface->inside)
		return TESS_UNDEF;
	return edge->Rface->n;
}