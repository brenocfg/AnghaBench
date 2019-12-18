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
struct TYPE_4__ {int numpoints; int /*<<< orphan*/ ** points; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_5__ {int hint; TYPE_1__* winding; scalar_t__ removed; } ;
typedef  TYPE_2__ vportal_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 char* PORTALFILE ; 
 int /*<<< orphan*/  WriteFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int numportals ; 
 TYPE_2__* portals ; 

void WritePortals(char *filename)
{
	int i, j, num;
	FILE *pf;
	vportal_t *p;
	winding_t *w;

	// write the file
	pf = fopen (filename, "w");
	if (!pf)
		Error ("Error opening %s", filename);

	num = 0;
	for (j = 0; j < numportals * 2; j++)
	{
		p = portals + j;
		if (p->removed)
			continue;
//		if (!p->hint)
//			continue;
		num++;
	}

	fprintf (pf, "%s\n", PORTALFILE);
	fprintf (pf, "%i\n", 0);
	fprintf (pf, "%i\n", num);// + numfaces);
	fprintf (pf, "%i\n", 0);

	for (j = 0; j < numportals * 2; j++)
	{
		p = portals + j;
		if (p->removed)
			continue;
//		if (!p->hint)
//			continue;
		w = p->winding;
		fprintf (pf,"%i %i %i ",w->numpoints, 0, 0);
		fprintf (pf, "%d ", p->hint);
		for (i=0 ; i<w->numpoints ; i++)
		{
			fprintf (pf,"(");
			WriteFloat (pf, w->points[i][0]);
			WriteFloat (pf, w->points[i][1]);
			WriteFloat (pf, w->points[i][2]);
			fprintf (pf,") ");
		}
		fprintf (pf,"\n");
	}

	/*
	for (j = 0; j < numfaces; j++)
	{
		p = faces + j;
		w = p->winding;
		fprintf (pf,"%i %i %i ",w->numpoints, 0, 0);
		fprintf (pf, "0 ");
		for (i=0 ; i<w->numpoints ; i++)
		{
			fprintf (pf,"(");
			WriteFloat (pf, w->points[i][0]);
			WriteFloat (pf, w->points[i][1]);
			WriteFloat (pf, w->points[i][2]);
			fprintf (pf,") ");
		}
		fprintf (pf,"\n");
	}*/

	fclose (pf);
}