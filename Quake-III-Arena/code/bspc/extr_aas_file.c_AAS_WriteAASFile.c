#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
typedef  int /*<<< orphan*/  aas_vertex_t ;
typedef  int /*<<< orphan*/  aas_reachability_t ;
typedef  int /*<<< orphan*/  aas_portalindex_t ;
typedef  int /*<<< orphan*/  aas_portal_t ;
typedef  int /*<<< orphan*/  aas_plane_t ;
typedef  int /*<<< orphan*/  aas_node_t ;
struct TYPE_6__ {void* bspchecksum; void* version; void* ident; } ;
typedef  TYPE_1__ aas_header_t ;
typedef  int /*<<< orphan*/  aas_faceindex_t ;
typedef  int /*<<< orphan*/  aas_face_t ;
typedef  int /*<<< orphan*/  aas_edgeindex_t ;
typedef  int /*<<< orphan*/  aas_edge_t ;
typedef  int /*<<< orphan*/  aas_cluster_t ;
typedef  int /*<<< orphan*/  aas_bbox_t ;
typedef  int /*<<< orphan*/  aas_areasettings_t ;
typedef  int /*<<< orphan*/  aas_area_t ;
struct TYPE_7__ {int numbboxes; int numvertexes; int numplanes; int numedges; int edgeindexsize; int numfaces; int faceindexsize; int numareas; int numareasettings; int reachabilitysize; int numnodes; int numportals; int portalindexsize; int numclusters; int /*<<< orphan*/  clusters; int /*<<< orphan*/  portalindex; int /*<<< orphan*/  portals; int /*<<< orphan*/  nodes; int /*<<< orphan*/  reachability; int /*<<< orphan*/  areasettings; int /*<<< orphan*/  areas; int /*<<< orphan*/  faceindex; int /*<<< orphan*/  faces; int /*<<< orphan*/  edgeindex; int /*<<< orphan*/  edges; int /*<<< orphan*/  planes; int /*<<< orphan*/  vertexes; int /*<<< orphan*/  bboxes; int /*<<< orphan*/  bspchecksum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AASID ; 
 int /*<<< orphan*/  AASLUMP_AREAS ; 
 int /*<<< orphan*/  AASLUMP_AREASETTINGS ; 
 int /*<<< orphan*/  AASLUMP_BBOXES ; 
 int /*<<< orphan*/  AASLUMP_CLUSTERS ; 
 int /*<<< orphan*/  AASLUMP_EDGEINDEX ; 
 int /*<<< orphan*/  AASLUMP_EDGES ; 
 int /*<<< orphan*/  AASLUMP_FACEINDEX ; 
 int /*<<< orphan*/  AASLUMP_FACES ; 
 int /*<<< orphan*/  AASLUMP_NODES ; 
 int /*<<< orphan*/  AASLUMP_PLANES ; 
 int /*<<< orphan*/  AASLUMP_PORTALINDEX ; 
 int /*<<< orphan*/  AASLUMP_PORTALS ; 
 int /*<<< orphan*/  AASLUMP_REACHABILITY ; 
 int /*<<< orphan*/  AASLUMP_VERTEXES ; 
 int /*<<< orphan*/  AASVERSION ; 
 int /*<<< orphan*/  AAS_DData (unsigned char*,int) ; 
 int /*<<< orphan*/  AAS_ShowTotals () ; 
 int /*<<< orphan*/  AAS_SwapAASData () ; 
 int /*<<< orphan*/  AAS_WriteAASLump (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* LittleLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_4__ aasworld ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

qboolean AAS_WriteAASFile(char *filename)
{
	aas_header_t header;
	FILE *fp;

	Log_Print("writing %s\n", filename);
	AAS_ShowTotals();
	//swap the aas data
	AAS_SwapAASData();
	//initialize the file header
	memset(&header, 0, sizeof(aas_header_t));
	header.ident = LittleLong(AASID);
	header.version = LittleLong(AASVERSION);
	header.bspchecksum = LittleLong(aasworld.bspchecksum);
	//open a new file
	fp = fopen(filename, "wb");
	if (!fp)
	{
		Log_Print("error opening %s\n", filename);
		return false;
	} //end if
	//write the header
	if (fwrite(&header, sizeof(aas_header_t), 1, fp) < 1)
	{
		fclose(fp);
		return false;
	} //end if
	//add the data lumps to the file
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_BBOXES, aasworld.bboxes,
		aasworld.numbboxes * sizeof(aas_bbox_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_VERTEXES, aasworld.vertexes,
		aasworld.numvertexes * sizeof(aas_vertex_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_PLANES, aasworld.planes,
		aasworld.numplanes * sizeof(aas_plane_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_EDGES, aasworld.edges,
		aasworld.numedges * sizeof(aas_edge_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_EDGEINDEX, aasworld.edgeindex,
		aasworld.edgeindexsize * sizeof(aas_edgeindex_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_FACES, aasworld.faces,
		aasworld.numfaces * sizeof(aas_face_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_FACEINDEX, aasworld.faceindex,
		aasworld.faceindexsize * sizeof(aas_faceindex_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_AREAS, aasworld.areas,
		aasworld.numareas * sizeof(aas_area_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_AREASETTINGS, aasworld.areasettings,
		aasworld.numareasettings * sizeof(aas_areasettings_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_REACHABILITY, aasworld.reachability,
		aasworld.reachabilitysize * sizeof(aas_reachability_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_NODES, aasworld.nodes,
		aasworld.numnodes * sizeof(aas_node_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_PORTALS, aasworld.portals,
		aasworld.numportals * sizeof(aas_portal_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_PORTALINDEX, aasworld.portalindex,
		aasworld.portalindexsize * sizeof(aas_portalindex_t))) return false;
	if (!AAS_WriteAASLump(fp, &header, AASLUMP_CLUSTERS, aasworld.clusters,
		aasworld.numclusters * sizeof(aas_cluster_t))) return false;
	//rewrite the header with the added lumps
	fseek(fp, 0, SEEK_SET);
	AAS_DData((unsigned char *) &header + 8, sizeof(aas_header_t) - 8);
	if (fwrite(&header, sizeof(aas_header_t), 1, fp) < 1)
	{
		fclose(fp);
		return false;
	} //end if
	//close the file
	fclose(fp);
	return true;
}