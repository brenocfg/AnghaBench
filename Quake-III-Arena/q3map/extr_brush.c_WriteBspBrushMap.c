#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__** p; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_9__ {size_t planenum; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_10__ {int numsides; TYPE_2__* sides; struct TYPE_10__* next; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_11__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* BaseWindingForPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 int /*<<< orphan*/  _printf (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_4__* mapplanes ; 

void WriteBspBrushMap (char *name, bspbrush_t *list)
{
	FILE	*f;
	side_t	*s;
	int		i;
	winding_t	*w;

	_printf ("writing %s\n", name);
	f = fopen (name, "wb");
	if (!f)
		Error ("Can't write %s\b", name);

	fprintf (f, "{\n\"classname\" \"worldspawn\"\n");

	for ( ; list ; list=list->next )
	{
		fprintf (f, "{\n");
		for (i=0,s=list->sides ; i<list->numsides ; i++,s++)
		{
			w = BaseWindingForPlane (mapplanes[s->planenum].normal, mapplanes[s->planenum].dist);

			fprintf (f,"( %i %i %i ) ", (int)w->p[0][0], (int)w->p[0][1], (int)w->p[0][2]);
			fprintf (f,"( %i %i %i ) ", (int)w->p[1][0], (int)w->p[1][1], (int)w->p[1][2]);
			fprintf (f,"( %i %i %i ) ", (int)w->p[2][0], (int)w->p[2][1], (int)w->p[2][2]);

			fprintf (f, "notexture 0 0 0 1 1\n" );
			FreeWinding (w);
		}
		fprintf (f, "}\n");
	}
	fprintf (f, "}\n");

	fclose (f);

}