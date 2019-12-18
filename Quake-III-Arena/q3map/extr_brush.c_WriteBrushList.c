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
struct TYPE_4__ {int /*<<< orphan*/  winding; int /*<<< orphan*/  visible; } ;
typedef  TYPE_1__ side_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_5__ {int numsides; TYPE_1__* sides; struct TYPE_5__* next; } ;
typedef  TYPE_2__ bspbrush_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OutputWinding (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SafeOpenWrite (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qprintf (char*,char*) ; 

void WriteBrushList (char *name, bspbrush_t *brush, qboolean onlyvis)
{
	int		i;
	side_t	*s;
	FILE	*f;

	qprintf ("writing %s\n", name);
	f = SafeOpenWrite (name);

	for ( ; brush ; brush=brush->next)
	{
		for (i=0 ; i<brush->numsides ; i++)
		{
			s = &brush->sides[i];
			if (!s->winding)
				continue;
			if (onlyvis && !s->visible)
				continue;
			OutputWinding (brush->sides[i].winding, f);
		}
	}

	fclose (f);
}