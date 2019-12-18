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
typedef  int /*<<< orphan*/  hl_texinfo_t ;
typedef  int /*<<< orphan*/  hl_dvertex_t ;
typedef  int /*<<< orphan*/  hl_dplane_t ;
typedef  int /*<<< orphan*/  hl_dnode_t ;
typedef  int /*<<< orphan*/  hl_dmodel_t ;
typedef  int /*<<< orphan*/  hl_dleaf_t ;
typedef  int /*<<< orphan*/  hl_dface_t ;
typedef  int /*<<< orphan*/  hl_dedge_t ;
typedef  int /*<<< orphan*/  hl_dclipnode_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 scalar_t__ GetMemory (int) ; 
 int HL_MAX_MAP_CLIPNODES ; 
 int HL_MAX_MAP_EDGES ; 
 int HL_MAX_MAP_ENTSTRING ; 
 int HL_MAX_MAP_FACES ; 
 int HL_MAX_MAP_LEAFS ; 
 int HL_MAX_MAP_LIGHTING ; 
 int HL_MAX_MAP_MARKSURFACES ; 
 int HL_MAX_MAP_MIPTEX ; 
 int HL_MAX_MAP_MODELS ; 
 int HL_MAX_MAP_NODES ; 
 int HL_MAX_MAP_PLANES ; 
 int HL_MAX_MAP_SURFEDGES ; 
 int HL_MAX_MAP_TEXINFO ; 
 int HL_MAX_MAP_VERTS ; 
 int HL_MAX_MAP_VISIBILITY ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  PrintMemorySize (int) ; 
 int hl_allocatedbspmem ; 
 int /*<<< orphan*/ * hl_dclipnodes ; 
 int /*<<< orphan*/ * hl_dedges ; 
 char* hl_dentdata ; 
 int /*<<< orphan*/ * hl_dfaces ; 
 int /*<<< orphan*/ * hl_dleafs ; 
 int /*<<< orphan*/ * hl_dlightdata ; 
 unsigned short* hl_dmarksurfaces ; 
 int /*<<< orphan*/ * hl_dmodels ; 
 int /*<<< orphan*/ * hl_dnodes ; 
 int /*<<< orphan*/ * hl_dplanes ; 
 int* hl_dsurfedges ; 
 int /*<<< orphan*/ * hl_dtexdata ; 
 int /*<<< orphan*/ * hl_dvertexes ; 
 int /*<<< orphan*/ * hl_dvisdata ; 
 scalar_t__ hl_entdatasize ; 
 scalar_t__ hl_lightdatasize ; 
 scalar_t__ hl_numclipnodes ; 
 scalar_t__ hl_numedges ; 
 scalar_t__ hl_numfaces ; 
 scalar_t__ hl_numleafs ; 
 scalar_t__ hl_nummarksurfaces ; 
 scalar_t__ hl_nummodels ; 
 scalar_t__ hl_numnodes ; 
 scalar_t__ hl_numplanes ; 
 scalar_t__ hl_numsurfedges ; 
 scalar_t__ hl_numtexinfo ; 
 scalar_t__ hl_numvertexes ; 
 scalar_t__ hl_texdatasize ; 
 int /*<<< orphan*/ * hl_texinfo ; 
 scalar_t__ hl_visdatasize ; 

void HL_AllocMaxBSP(void)
{
	//models
	hl_nummodels = 0;
	hl_dmodels = (hl_dmodel_t *) GetMemory(HL_MAX_MAP_MODELS * sizeof(hl_dmodel_t));
	hl_allocatedbspmem = HL_MAX_MAP_MODELS * sizeof(hl_dmodel_t);
	//visibility
	hl_visdatasize = 0;
	hl_dvisdata = (byte *) GetMemory(HL_MAX_MAP_VISIBILITY * sizeof(byte));
	hl_allocatedbspmem += HL_MAX_MAP_VISIBILITY * sizeof(byte);
	//light data
	hl_lightdatasize = 0;
	hl_dlightdata = (byte *) GetMemory(HL_MAX_MAP_LIGHTING * sizeof(byte));
	hl_allocatedbspmem += HL_MAX_MAP_LIGHTING * sizeof(byte);
	//texture data
	hl_texdatasize = 0;
	hl_dtexdata = (byte *) GetMemory(HL_MAX_MAP_MIPTEX * sizeof(byte)); // (dmiptexlump_t)
	hl_allocatedbspmem += HL_MAX_MAP_MIPTEX * sizeof(byte);
	//entities
	hl_entdatasize = 0;
	hl_dentdata = (char *) GetMemory(HL_MAX_MAP_ENTSTRING * sizeof(char));
	hl_allocatedbspmem += HL_MAX_MAP_ENTSTRING * sizeof(char);
	//leaves
	hl_numleafs = 0;
	hl_dleafs = (hl_dleaf_t *) GetMemory(HL_MAX_MAP_LEAFS * sizeof(hl_dleaf_t));
	hl_allocatedbspmem += HL_MAX_MAP_LEAFS * sizeof(hl_dleaf_t);
	//planes
	hl_numplanes = 0;
	hl_dplanes = (hl_dplane_t *) GetMemory(HL_MAX_MAP_PLANES * sizeof(hl_dplane_t));
	hl_allocatedbspmem += HL_MAX_MAP_PLANES * sizeof(hl_dplane_t);
	//vertexes
	hl_numvertexes = 0;
	hl_dvertexes = (hl_dvertex_t *) GetMemory(HL_MAX_MAP_VERTS * sizeof(hl_dvertex_t));
	hl_allocatedbspmem += HL_MAX_MAP_VERTS * sizeof(hl_dvertex_t);
	//nodes
	hl_numnodes = 0;
	hl_dnodes = (hl_dnode_t *) GetMemory(HL_MAX_MAP_NODES * sizeof(hl_dnode_t));
	hl_allocatedbspmem += HL_MAX_MAP_NODES * sizeof(hl_dnode_t);
	//texture info
	hl_numtexinfo = 0;
	hl_texinfo = (hl_texinfo_t *) GetMemory(HL_MAX_MAP_TEXINFO * sizeof(hl_texinfo_t));
	hl_allocatedbspmem += HL_MAX_MAP_TEXINFO * sizeof(hl_texinfo_t);
	//faces
	hl_numfaces = 0;
	hl_dfaces = (hl_dface_t *) GetMemory(HL_MAX_MAP_FACES * sizeof(hl_dface_t));
	hl_allocatedbspmem += HL_MAX_MAP_FACES * sizeof(hl_dface_t);
	//clip nodes
	hl_numclipnodes = 0;
	hl_dclipnodes = (hl_dclipnode_t *) GetMemory(HL_MAX_MAP_CLIPNODES * sizeof(hl_dclipnode_t));
	hl_allocatedbspmem += HL_MAX_MAP_CLIPNODES * sizeof(hl_dclipnode_t);
	//edges
	hl_numedges = 0;
	hl_dedges = (hl_dedge_t *) GetMemory(HL_MAX_MAP_EDGES * sizeof(hl_dedge_t));
	hl_allocatedbspmem += HL_MAX_MAP_EDGES, sizeof(hl_dedge_t);
	//mark surfaces
	hl_nummarksurfaces = 0;
	hl_dmarksurfaces = (unsigned short *) GetMemory(HL_MAX_MAP_MARKSURFACES * sizeof(unsigned short));
	hl_allocatedbspmem += HL_MAX_MAP_MARKSURFACES * sizeof(unsigned short);
	//surface edges
	hl_numsurfedges = 0;
	hl_dsurfedges = (int *) GetMemory(HL_MAX_MAP_SURFEDGES * sizeof(int));
	hl_allocatedbspmem += HL_MAX_MAP_SURFEDGES * sizeof(int);
	//print allocated memory
	Log_Print("allocated ");
	PrintMemorySize(hl_allocatedbspmem);
	Log_Print(" of BSP memory\n");
}