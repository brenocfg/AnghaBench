#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dvis_t ;
typedef  int /*<<< orphan*/  dvertex_t ;
typedef  int /*<<< orphan*/  dplane_t ;
typedef  int /*<<< orphan*/  dnode_t ;
typedef  int /*<<< orphan*/  dmodel_t ;
typedef  int /*<<< orphan*/  dleaf_t ;
typedef  int /*<<< orphan*/  dface_t ;
typedef  int /*<<< orphan*/  dedge_t ;
typedef  int /*<<< orphan*/  dbrushside_t ;
typedef  int /*<<< orphan*/  dbrush_t ;
typedef  int /*<<< orphan*/  dareaportal_t ;
typedef  int /*<<< orphan*/  darea_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int MAX_MAP_AREAPORTALS ; 
 int MAX_MAP_AREAS ; 
 int MAX_MAP_BRUSHES ; 
 int MAX_MAP_BRUSHSIDES ; 
 int MAX_MAP_EDGES ; 
 int MAX_MAP_ENTSTRING ; 
 int MAX_MAP_FACES ; 
 int MAX_MAP_LEAFBRUSHES ; 
 int MAX_MAP_LEAFFACES ; 
 int MAX_MAP_LEAFS ; 
 int MAX_MAP_LIGHTING ; 
 int MAX_MAP_MODELS ; 
 int MAX_MAP_NODES ; 
 int MAX_MAP_PLANES ; 
 int MAX_MAP_SURFEDGES ; 
 int MAX_MAP_VERTS ; 
 int MAX_MAP_VISIBILITY ; 
 int /*<<< orphan*/  PrintMemorySize (int) ; 
 int allocatedbspmem ; 
 int /*<<< orphan*/ * dareaportals ; 
 int /*<<< orphan*/ * dareas ; 
 int /*<<< orphan*/ * dbrushes ; 
 int /*<<< orphan*/ * dbrushsides ; 
 int /*<<< orphan*/ * dedges ; 
 char* dentdata ; 
 int /*<<< orphan*/ * dfaces ; 
 unsigned short* dleafbrushes ; 
 unsigned short* dleaffaces ; 
 int /*<<< orphan*/ * dleafs ; 
 int /*<<< orphan*/ * dlightdata ; 
 int /*<<< orphan*/ * dmodels ; 
 int /*<<< orphan*/ * dnodes ; 
 int /*<<< orphan*/ * dplanes ; 
 int* dsurfedges ; 
 int /*<<< orphan*/ * dvertexes ; 
 int /*<<< orphan*/ * dvis ; 
 int /*<<< orphan*/ * dvisdata ; 
 scalar_t__ entdatasize ; 
 scalar_t__ lightdatasize ; 
 scalar_t__ numareaportals ; 
 scalar_t__ numareas ; 
 scalar_t__ numbrushes ; 
 scalar_t__ numbrushsides ; 
 scalar_t__ numedges ; 
 scalar_t__ numfaces ; 
 scalar_t__ numleafbrushes ; 
 scalar_t__ numleaffaces ; 
 scalar_t__ numleafs ; 
 scalar_t__ nummodels ; 
 scalar_t__ numnodes ; 
 scalar_t__ numplanes ; 
 scalar_t__ numsurfedges ; 
 scalar_t__ numvertexes ; 
 scalar_t__ visdatasize ; 

void Q2_AllocMaxBSP(void)
{
	//models
	nummodels = 0;
	dmodels = (dmodel_t *) GetClearedMemory(MAX_MAP_MODELS * sizeof(dmodel_t));
	allocatedbspmem += MAX_MAP_MODELS * sizeof(dmodel_t);
	//vis data
	visdatasize = 0;
	dvisdata = (byte *) GetClearedMemory(MAX_MAP_VISIBILITY * sizeof(byte));
	dvis = (dvis_t *) dvisdata;
	allocatedbspmem += MAX_MAP_VISIBILITY * sizeof(byte);
	//light data
	lightdatasize = 0;
	dlightdata = (byte *) GetClearedMemory(MAX_MAP_LIGHTING * sizeof(byte));
	allocatedbspmem += MAX_MAP_LIGHTING * sizeof(byte);
	//entity data
	entdatasize = 0;
	dentdata = (char *) GetClearedMemory(MAX_MAP_ENTSTRING * sizeof(char));
	allocatedbspmem += MAX_MAP_ENTSTRING * sizeof(char);
	//leafs
	numleafs = 0;
	dleafs = (dleaf_t *) GetClearedMemory(MAX_MAP_LEAFS * sizeof(dleaf_t));
	allocatedbspmem += MAX_MAP_LEAFS * sizeof(dleaf_t);
	//planes
	numplanes = 0;
	dplanes = (dplane_t *) GetClearedMemory(MAX_MAP_PLANES * sizeof(dplane_t));
	allocatedbspmem += MAX_MAP_PLANES * sizeof(dplane_t);
	//vertexes
	numvertexes = 0;
	dvertexes = (dvertex_t *) GetClearedMemory(MAX_MAP_VERTS * sizeof(dvertex_t));
	allocatedbspmem += MAX_MAP_VERTS * sizeof(dvertex_t);
	//nodes
	numnodes = 0;
	dnodes = (dnode_t *) GetClearedMemory(MAX_MAP_NODES * sizeof(dnode_t));
	allocatedbspmem += MAX_MAP_NODES * sizeof(dnode_t);
	/*
	//texture info
	numtexinfo = 0;
	texinfo = (texinfo_t *) GetClearedMemory(MAX_MAP_TEXINFO * sizeof(texinfo_t));
	allocatedbspmem += MAX_MAP_TEXINFO * sizeof(texinfo_t);
	//*/
	//faces
	numfaces = 0;
	dfaces = (dface_t *) GetClearedMemory(MAX_MAP_FACES * sizeof(dface_t));
	allocatedbspmem += MAX_MAP_FACES * sizeof(dface_t);
	//edges
	numedges = 0;
	dedges = (dedge_t *) GetClearedMemory(MAX_MAP_EDGES * sizeof(dedge_t));
	allocatedbspmem += MAX_MAP_EDGES * sizeof(dedge_t);
	//leaf faces
	numleaffaces = 0;
	dleaffaces = (unsigned short *) GetClearedMemory(MAX_MAP_LEAFFACES * sizeof(unsigned short));
	allocatedbspmem += MAX_MAP_LEAFFACES * sizeof(unsigned short);
	//leaf brushes
	numleafbrushes = 0;
	dleafbrushes = (unsigned short *) GetClearedMemory(MAX_MAP_LEAFBRUSHES * sizeof(unsigned short));
	allocatedbspmem += MAX_MAP_LEAFBRUSHES * sizeof(unsigned short);
	//surface edges
	numsurfedges = 0;
	dsurfedges = (int *) GetClearedMemory(MAX_MAP_SURFEDGES * sizeof(int));
	allocatedbspmem += MAX_MAP_SURFEDGES * sizeof(int);
	//brushes
	numbrushes = 0;
	dbrushes = (dbrush_t *) GetClearedMemory(MAX_MAP_BRUSHES * sizeof(dbrush_t));
	allocatedbspmem += MAX_MAP_BRUSHES * sizeof(dbrush_t);
	//brushsides
	numbrushsides = 0;
	dbrushsides = (dbrushside_t *) GetClearedMemory(MAX_MAP_BRUSHSIDES * sizeof(dbrushside_t));
	allocatedbspmem += MAX_MAP_BRUSHSIDES * sizeof(dbrushside_t);
	//areas
	numareas = 0;
	dareas = (darea_t *) GetClearedMemory(MAX_MAP_AREAS * sizeof(darea_t));
	allocatedbspmem += MAX_MAP_AREAS * sizeof(darea_t);
	//area portals
	numareaportals = 0;
	dareaportals = (dareaportal_t *) GetClearedMemory(MAX_MAP_AREAPORTALS * sizeof(dareaportal_t));
	allocatedbspmem += MAX_MAP_AREAPORTALS * sizeof(dareaportal_t);
	//print allocated memory
	Log_Print("allocated ");
	PrintMemorySize(allocatedbspmem);
	Log_Print(" of BSP memory\n");
}