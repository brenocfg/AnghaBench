#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int numpoints; double** points; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_13__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_14__ {size_t numportals; int leaf; TYPE_2__ plane; TYPE_1__* winding; struct TYPE_14__** portals; } ;
typedef  TYPE_3__ lportal_t ;
typedef  TYPE_3__ lleaf_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,...) ; 
 int MAX_CLUSTERS ; 
 int MAX_POINTS_ON_WINDING ; 
 size_t MAX_PORTALS_ON_LEAF ; 
 char* PORTALFILE ; 
 void* VS_AllocWinding (int) ; 
 int /*<<< orphan*/  VS_PlaneFromWinding (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VS_SetPortalSphere (TYPE_3__*) ; 
 int /*<<< orphan*/  VectorCopy (double*,double*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _printf (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__* leafs ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int numfaces ; 
 int numportals ; 
 int portalclusters ; 
 TYPE_3__* portals ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  vec3_origin ; 

void VS_LoadPortals (char *name)
{
	int			i, j, hint;
	lportal_t	*p;
	lleaf_t		*l;
	char		magic[80];
	FILE		*f;
	int			numpoints;
	winding_t	*w;
	int			leafnums[2];
	plane_t		plane;
	//
	
	if (!strcmp(name,"-"))
		f = stdin;
	else
	{
		f = fopen(name, "r");
		if (!f)
			Error ("LoadPortals: couldn't read %s\n",name);
	}

	if (fscanf (f,"%79s\n%i\n%i\n%i\n",magic, &portalclusters, &numportals, &numfaces) != 4)
		Error ("LoadPortals: failed to read header");
	if (strcmp(magic, PORTALFILE))
		Error ("LoadPortals: not a portal file");

	_printf ("%6i portalclusters\n", portalclusters);
	_printf ("%6i numportals\n", numportals);
	_printf ("%6i numfaces\n", numfaces);

	if (portalclusters >= MAX_CLUSTERS)
		Error ("more than %d clusters in portal file\n", MAX_CLUSTERS);

	// each file portal is split into two memory portals
	portals = malloc(2*numportals*sizeof(lportal_t));
	memset (portals, 0, 2*numportals*sizeof(lportal_t));
	
	leafs = malloc(portalclusters*sizeof(lleaf_t));
	memset (leafs, 0, portalclusters*sizeof(lleaf_t));

	for (i=0, p=portals ; i<numportals ; i++)
	{
		if (fscanf (f, "%i %i %i ", &numpoints, &leafnums[0], &leafnums[1]) != 3)
			Error ("LoadPortals: reading portal %i", i);
		if (numpoints > MAX_POINTS_ON_WINDING)
			Error ("LoadPortals: portal %i has too many points", i);
		if ( (unsigned)leafnums[0] > portalclusters
		|| (unsigned)leafnums[1] > portalclusters)
			Error ("LoadPortals: reading portal %i", i);
		if (fscanf (f, "%i ", &hint) != 1)
			Error ("LoadPortals: reading hint state");
		
		w = p->winding = VS_AllocWinding (numpoints);
		w->numpoints = numpoints;
		
		for (j=0 ; j<numpoints ; j++)
		{
			double	v[3];
			int		k;

			// scanf into double, then assign to vec_t
			// so we don't care what size vec_t is
			if (fscanf (f, "(%lf %lf %lf ) "
			, &v[0], &v[1], &v[2]) != 3)
				Error ("LoadPortals: reading portal %i", i);
			for (k=0 ; k<3 ; k++)
				w->points[j][k] = v[k];
		}
		fscanf (f, "\n");
		
		// calc plane
		VS_PlaneFromWinding (w, &plane);

		// create forward portal
		l = &leafs[leafnums[0]];
		if (l->numportals == MAX_PORTALS_ON_LEAF)
			Error ("Leaf with too many portals");
		l->portals[l->numportals] = p;
		l->numportals++;
		
		p->winding = w;
		VectorSubtract (vec3_origin, plane.normal, p->plane.normal);
		p->plane.dist = -plane.dist;
		p->leaf = leafnums[1];
		VS_SetPortalSphere (p);
		p++;
		
		// create backwards portal
		l = &leafs[leafnums[1]];
		if (l->numportals == MAX_PORTALS_ON_LEAF)
			Error ("Leaf with too many portals");
		l->portals[l->numportals] = p;
		l->numportals++;
		
		p->winding = VS_AllocWinding(w->numpoints);
		p->winding->numpoints = w->numpoints;
		for (j=0 ; j<w->numpoints ; j++)
		{
			VectorCopy (w->points[w->numpoints-1-j], p->winding->points[j]);
		}

		p->plane = plane;
		p->leaf = leafnums[0];
		VS_SetPortalSphere (p);
		p++;

	}
	
	fclose (f);
}