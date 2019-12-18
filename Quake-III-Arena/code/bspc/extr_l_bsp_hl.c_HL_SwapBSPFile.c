#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_14__ {int* headnode; int visleafs; int firstface; int numfaces; void** origin; void** maxs; void** mins; } ;
typedef  TYPE_1__ hl_dmodel_t ;
struct TYPE_15__ {int nummiptex; int* dataofs; } ;
typedef  TYPE_2__ hl_dmiptexlump_t ;
struct TYPE_21__ {int lightofs; int firstedge; void* numedges; void* side; void* planenum; void* texinfo; } ;
struct TYPE_20__ {int contents; int visofs; void* nummarksurfaces; void* firstmarksurface; void** maxs; void** mins; } ;
struct TYPE_19__ {int planenum; void* numfaces; void* firstface; void** children; void** maxs; void** mins; } ;
struct TYPE_18__ {int type; void* dist; void** normal; } ;
struct TYPE_17__ {void** point; } ;
struct TYPE_16__ {int miptex; int flags; void*** vecs; } ;
struct TYPE_13__ {int planenum; void** children; } ;
struct TYPE_12__ {void** v; } ;

/* Variables and functions */
 int HL_MAX_MAP_HULLS ; 
 void* LittleFloat (void*) ; 
 void* LittleLong (int) ; 
 void* LittleShort (void*) ; 
 TYPE_11__* hl_dclipnodes ; 
 TYPE_10__* hl_dedges ; 
 TYPE_9__* hl_dfaces ; 
 TYPE_8__* hl_dleafs ; 
 void** hl_dmarksurfaces ; 
 TYPE_1__* hl_dmodels ; 
 TYPE_6__* hl_dnodes ; 
 TYPE_5__* hl_dplanes ; 
 int* hl_dsurfedges ; 
 scalar_t__ hl_dtexdata ; 
 TYPE_4__* hl_dvertexes ; 
 int hl_numclipnodes ; 
 int hl_numedges ; 
 int hl_numfaces ; 
 int hl_numleafs ; 
 int hl_nummarksurfaces ; 
 int hl_nummodels ; 
 int hl_numnodes ; 
 int hl_numplanes ; 
 int hl_numsurfedges ; 
 int hl_numtexinfo ; 
 int hl_numvertexes ; 
 scalar_t__ hl_texdatasize ; 
 TYPE_3__* hl_texinfo ; 

void HL_SwapBSPFile (qboolean todisk)
{
	int i, j, c;
	hl_dmodel_t *d;
	hl_dmiptexlump_t *mtl;

	
// models	
	for (i = 0; i < hl_nummodels; i++)
	{
		d = &hl_dmodels[i];

		for (j = 0; j < HL_MAX_MAP_HULLS; j++)
			d->headnode[j] = LittleLong(d->headnode[j]);

		d->visleafs = LittleLong(d->visleafs);
		d->firstface = LittleLong(d->firstface);
		d->numfaces = LittleLong(d->numfaces);
		
		for (j = 0; j < 3; j++)
		{
			d->mins[j] = LittleFloat(d->mins[j]);
			d->maxs[j] = LittleFloat(d->maxs[j]);
			d->origin[j] = LittleFloat(d->origin[j]);
		}
	}

//
// vertexes
//
	for (i = 0; i < hl_numvertexes; i++)
	{
		for (j = 0; j < 3; j++)
			hl_dvertexes[i].point[j] = LittleFloat (hl_dvertexes[i].point[j]);
	}
		
//
// planes
//	
	for (i=0 ; i<hl_numplanes ; i++)
	{
		for (j=0 ; j<3 ; j++)
			hl_dplanes[i].normal[j] = LittleFloat (hl_dplanes[i].normal[j]);
		hl_dplanes[i].dist = LittleFloat (hl_dplanes[i].dist);
		hl_dplanes[i].type = LittleLong (hl_dplanes[i].type);
	}
	
//
// texinfos
//	
	for (i=0 ; i<hl_numtexinfo ; i++)
	{
		for (j=0 ; j<8 ; j++)
			hl_texinfo[i].vecs[0][j] = LittleFloat (hl_texinfo[i].vecs[0][j]);
		hl_texinfo[i].miptex = LittleLong (hl_texinfo[i].miptex);
		hl_texinfo[i].flags = LittleLong (hl_texinfo[i].flags);
	}
	
//
// faces
//
	for (i=0 ; i<hl_numfaces ; i++)
	{
		hl_dfaces[i].texinfo = LittleShort (hl_dfaces[i].texinfo);
		hl_dfaces[i].planenum = LittleShort (hl_dfaces[i].planenum);
		hl_dfaces[i].side = LittleShort (hl_dfaces[i].side);
		hl_dfaces[i].lightofs = LittleLong (hl_dfaces[i].lightofs);
		hl_dfaces[i].firstedge = LittleLong (hl_dfaces[i].firstedge);
		hl_dfaces[i].numedges = LittleShort (hl_dfaces[i].numedges);
	}

//
// nodes
//
	for (i=0 ; i<hl_numnodes ; i++)
	{
		hl_dnodes[i].planenum = LittleLong (hl_dnodes[i].planenum);
		for (j=0 ; j<3 ; j++)
		{
			hl_dnodes[i].mins[j] = LittleShort (hl_dnodes[i].mins[j]);
			hl_dnodes[i].maxs[j] = LittleShort (hl_dnodes[i].maxs[j]);
		}
		hl_dnodes[i].children[0] = LittleShort (hl_dnodes[i].children[0]);
		hl_dnodes[i].children[1] = LittleShort (hl_dnodes[i].children[1]);
		hl_dnodes[i].firstface = LittleShort (hl_dnodes[i].firstface);
		hl_dnodes[i].numfaces = LittleShort (hl_dnodes[i].numfaces);
	}

//
// leafs
//
	for (i=0 ; i<hl_numleafs ; i++)
	{
		hl_dleafs[i].contents = LittleLong (hl_dleafs[i].contents);
		for (j=0 ; j<3 ; j++)
		{
			hl_dleafs[i].mins[j] = LittleShort (hl_dleafs[i].mins[j]);
			hl_dleafs[i].maxs[j] = LittleShort (hl_dleafs[i].maxs[j]);
		}

		hl_dleafs[i].firstmarksurface = LittleShort (hl_dleafs[i].firstmarksurface);
		hl_dleafs[i].nummarksurfaces = LittleShort (hl_dleafs[i].nummarksurfaces);
		hl_dleafs[i].visofs = LittleLong (hl_dleafs[i].visofs);
	}

//
// clipnodes
//
	for (i=0 ; i<hl_numclipnodes ; i++)
	{
		hl_dclipnodes[i].planenum = LittleLong (hl_dclipnodes[i].planenum);
		hl_dclipnodes[i].children[0] = LittleShort (hl_dclipnodes[i].children[0]);
		hl_dclipnodes[i].children[1] = LittleShort (hl_dclipnodes[i].children[1]);
	}

//
// miptex
//
	if (hl_texdatasize)
	{
		mtl = (hl_dmiptexlump_t *)hl_dtexdata;
		if (todisk)
			c = mtl->nummiptex;
		else
			c = LittleLong(mtl->nummiptex);
		mtl->nummiptex = LittleLong (mtl->nummiptex);
		for (i=0 ; i<c ; i++)
			mtl->dataofs[i] = LittleLong(mtl->dataofs[i]);
	}
	
//
// marksurfaces
//
	for (i=0 ; i<hl_nummarksurfaces ; i++)
		hl_dmarksurfaces[i] = LittleShort (hl_dmarksurfaces[i]);

//
// surfedges
//
	for (i=0 ; i<hl_numsurfedges ; i++)
		hl_dsurfedges[i] = LittleLong (hl_dsurfedges[i]);

//
// edges
//
	for (i=0 ; i<hl_numedges ; i++)
	{
		hl_dedges[i].v[0] = LittleShort (hl_dedges[i].v[0]);
		hl_dedges[i].v[1] = LittleShort (hl_dedges[i].v[1]);
	}
}