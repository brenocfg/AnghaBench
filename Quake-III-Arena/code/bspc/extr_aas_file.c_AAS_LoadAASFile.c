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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
typedef  int /*<<< orphan*/  aas_vertex_t ;
typedef  int /*<<< orphan*/  aas_reachability_t ;
typedef  int /*<<< orphan*/  aas_portalindex_t ;
typedef  int /*<<< orphan*/  aas_portal_t ;
typedef  int /*<<< orphan*/  aas_plane_t ;
typedef  int /*<<< orphan*/  aas_node_t ;
struct TYPE_6__ {scalar_t__ ident; scalar_t__ version; scalar_t__ bspchecksum; TYPE_1__* lumps; } ;
typedef  TYPE_2__ aas_header_t ;
typedef  int /*<<< orphan*/  aas_faceindex_t ;
typedef  int /*<<< orphan*/  aas_face_t ;
typedef  int /*<<< orphan*/  aas_edgeindex_t ;
typedef  int /*<<< orphan*/  aas_edge_t ;
typedef  int /*<<< orphan*/  aas_cluster_t ;
typedef  int /*<<< orphan*/  aas_bbox_t ;
typedef  int /*<<< orphan*/  aas_areasettings_t ;
typedef  int /*<<< orphan*/  aas_area_t ;
struct TYPE_7__ {int numbboxes; int numvertexes; int numplanes; int numedges; int edgeindexsize; int numfaces; int faceindexsize; int numareas; int numareasettings; int reachabilitysize; int numnodes; int numportals; int portalindexsize; int numclusters; int loaded; int /*<<< orphan*/ * clusters; int /*<<< orphan*/ * portalindex; int /*<<< orphan*/ * portals; int /*<<< orphan*/ * nodes; int /*<<< orphan*/ * reachability; int /*<<< orphan*/ * areasettings; int /*<<< orphan*/ * areas; int /*<<< orphan*/ * faceindex; int /*<<< orphan*/ * faces; int /*<<< orphan*/ * edgeindex; int /*<<< orphan*/ * edges; int /*<<< orphan*/ * planes; int /*<<< orphan*/ * vertexes; int /*<<< orphan*/ * bboxes; void* bspchecksum; } ;
struct TYPE_5__ {scalar_t__ fileofs; scalar_t__ filelen; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AASID ; 
 size_t AASLUMP_AREAS ; 
 size_t AASLUMP_AREASETTINGS ; 
 size_t AASLUMP_BBOXES ; 
 size_t AASLUMP_CLUSTERS ; 
 size_t AASLUMP_EDGEINDEX ; 
 size_t AASLUMP_EDGES ; 
 size_t AASLUMP_FACEINDEX ; 
 size_t AASLUMP_FACES ; 
 size_t AASLUMP_NODES ; 
 size_t AASLUMP_PLANES ; 
 size_t AASLUMP_PORTALINDEX ; 
 size_t AASLUMP_PORTALS ; 
 size_t AASLUMP_REACHABILITY ; 
 size_t AASLUMP_VERTEXES ; 
 scalar_t__ AASVERSION ; 
 scalar_t__ AASVERSION_OLD ; 
 int /*<<< orphan*/  AAS_DData (unsigned char*,int) ; 
 int /*<<< orphan*/  AAS_DumpAASData () ; 
 int /*<<< orphan*/  AAS_Error (char*,...) ; 
 scalar_t__ AAS_LoadAASLump (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AAS_SwapAASData () ; 
 void* LittleLong (scalar_t__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_4__ aasworld ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

qboolean AAS_LoadAASFile(char *filename, int fpoffset, int fplength)
{
	FILE *fp;
	aas_header_t header;
	int offset, length;

	//dump current loaded aas file
	AAS_DumpAASData();
	//open the file
	fp = fopen(filename, "rb");
	if (!fp)
	{
		AAS_Error("can't open %s\n", filename);
		return false;
	} //end if
	//seek to the correct position (in the pak file)
	if (fseek(fp, fpoffset, SEEK_SET))
	{
		AAS_Error("can't seek to file %s\n");
		fclose(fp);
		return false;
	} //end if
	//read the header
	if (fread(&header, sizeof(aas_header_t), 1, fp) != 1)
	{
		AAS_Error("can't read header of file %s\n", filename);
		fclose(fp);
		return false;
	} //end if
	//check header identification
	header.ident = LittleLong(header.ident);
	if (header.ident != AASID)
	{
		AAS_Error("%s is not an AAS file\n", filename);
		fclose(fp);
		return false;
	} //end if
	//check the version
	header.version = LittleLong(header.version);
	if (header.version != AASVERSION_OLD && header.version != AASVERSION)
	{
		AAS_Error("%s is version %i, not %i\n", filename, header.version, AASVERSION);
		fclose(fp);
		return false;
	} //end if
	//
	if (header.version == AASVERSION)
	{
		AAS_DData((unsigned char *) &header + 8, sizeof(aas_header_t) - 8);
	} //end if
	aasworld.bspchecksum = LittleLong(header.bspchecksum);
	//load the lumps:
	//bounding boxes
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_BBOXES].fileofs);
	length = LittleLong(header.lumps[AASLUMP_BBOXES].filelen);
	aasworld.bboxes = (aas_bbox_t *) AAS_LoadAASLump(fp, offset, length, aasworld.bboxes);
	if (!aasworld.bboxes) return false;
	aasworld.numbboxes = length / sizeof(aas_bbox_t);
	//vertexes
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_VERTEXES].fileofs);
	length = LittleLong(header.lumps[AASLUMP_VERTEXES].filelen);
	aasworld.vertexes = (aas_vertex_t *) AAS_LoadAASLump(fp, offset, length, aasworld.vertexes);
	if (!aasworld.vertexes) return false;
	aasworld.numvertexes = length / sizeof(aas_vertex_t);
	//planes
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_PLANES].fileofs);
	length = LittleLong(header.lumps[AASLUMP_PLANES].filelen);
	aasworld.planes = (aas_plane_t *) AAS_LoadAASLump(fp, offset, length, aasworld.planes);
	if (!aasworld.planes) return false;
	aasworld.numplanes = length / sizeof(aas_plane_t);
	//edges
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_EDGES].fileofs);
	length = LittleLong(header.lumps[AASLUMP_EDGES].filelen);
	aasworld.edges = (aas_edge_t *) AAS_LoadAASLump(fp, offset, length, aasworld.edges);
	if (!aasworld.edges) return false;
	aasworld.numedges = length / sizeof(aas_edge_t);
	//edgeindex
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_EDGEINDEX].fileofs);
	length = LittleLong(header.lumps[AASLUMP_EDGEINDEX].filelen);
	aasworld.edgeindex = (aas_edgeindex_t *) AAS_LoadAASLump(fp, offset, length, aasworld.edgeindex);
	if (!aasworld.edgeindex) return false;
	aasworld.edgeindexsize = length / sizeof(aas_edgeindex_t);
	//faces
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_FACES].fileofs);
	length = LittleLong(header.lumps[AASLUMP_FACES].filelen);
	aasworld.faces = (aas_face_t *) AAS_LoadAASLump(fp, offset, length, aasworld.faces);
	if (!aasworld.faces) return false;
	aasworld.numfaces = length / sizeof(aas_face_t);
	//faceindex
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_FACEINDEX].fileofs);
	length = LittleLong(header.lumps[AASLUMP_FACEINDEX].filelen);
	aasworld.faceindex = (aas_faceindex_t *) AAS_LoadAASLump(fp, offset, length, aasworld.faceindex);
	if (!aasworld.faceindex) return false;
	aasworld.faceindexsize = length / sizeof(int);
	//convex areas
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_AREAS].fileofs);
	length = LittleLong(header.lumps[AASLUMP_AREAS].filelen);
	aasworld.areas = (aas_area_t *) AAS_LoadAASLump(fp, offset, length, aasworld.areas);
	if (!aasworld.areas) return false;
	aasworld.numareas = length / sizeof(aas_area_t);
	//area settings
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_AREASETTINGS].fileofs);
	length = LittleLong(header.lumps[AASLUMP_AREASETTINGS].filelen);
	aasworld.areasettings = (aas_areasettings_t *) AAS_LoadAASLump(fp, offset, length, aasworld.areasettings);
	if (!aasworld.areasettings) return false;
	aasworld.numareasettings = length / sizeof(aas_areasettings_t);
	//reachability list
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_REACHABILITY].fileofs);
	length = LittleLong(header.lumps[AASLUMP_REACHABILITY].filelen);
	aasworld.reachability = (aas_reachability_t *) AAS_LoadAASLump(fp, offset, length, aasworld.reachability);
	if (length && !aasworld.reachability) return false;
	aasworld.reachabilitysize = length / sizeof(aas_reachability_t);
	//nodes
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_NODES].fileofs);
	length = LittleLong(header.lumps[AASLUMP_NODES].filelen);
	aasworld.nodes = (aas_node_t *) AAS_LoadAASLump(fp, offset, length, aasworld.nodes);
	if (!aasworld.nodes) return false;
	aasworld.numnodes = length / sizeof(aas_node_t);
	//cluster portals
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_PORTALS].fileofs);
	length = LittleLong(header.lumps[AASLUMP_PORTALS].filelen);
	aasworld.portals = (aas_portal_t *) AAS_LoadAASLump(fp, offset, length, aasworld.portals);
	if (length && !aasworld.portals) return false;
	aasworld.numportals = length / sizeof(aas_portal_t);
	//cluster portal index
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_PORTALINDEX].fileofs);
	length = LittleLong(header.lumps[AASLUMP_PORTALINDEX].filelen);
	aasworld.portalindex = (aas_portalindex_t *) AAS_LoadAASLump(fp, offset, length, aasworld.portalindex);
	if (length && !aasworld.portalindex) return false;
	aasworld.portalindexsize = length / sizeof(aas_portalindex_t);
	//clusters
	offset = fpoffset + LittleLong(header.lumps[AASLUMP_CLUSTERS].fileofs);
	length = LittleLong(header.lumps[AASLUMP_CLUSTERS].filelen);
	aasworld.clusters = (aas_cluster_t *) AAS_LoadAASLump(fp, offset, length, aasworld.clusters);
	if (length && !aasworld.clusters) return false;
	aasworld.numclusters = length / sizeof(aas_cluster_t);
	//swap everything
	AAS_SwapAASData();
	//aas file is loaded
	aasworld.loaded = true;
	//close the file
	fclose(fp);
	return true;
}