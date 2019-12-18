#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ident; scalar_t__ version; int numareas; int numclusters; scalar_t__ areacrc; scalar_t__ clustercrc; int numportalcache; int numareacache; } ;
typedef  TYPE_1__ routecacheheader_t ;
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_8__ {size_t areanum; size_t cluster; struct TYPE_8__* prev; struct TYPE_8__* next; } ;
typedef  TYPE_2__ aas_routingcache_t ;
typedef  int /*<<< orphan*/  aas_cluster_t ;
typedef  int /*<<< orphan*/  aas_area_t ;
struct TYPE_10__ {int numareas; int numclusters; TYPE_2__*** clusterareacache; TYPE_2__** portalcache; scalar_t__ clusters; scalar_t__ areas; int /*<<< orphan*/  mapname; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* FS_FCloseFile ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_Read ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_FOpenFile ) (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AAS_ClusterAreaNum (size_t,size_t) ; 
 int /*<<< orphan*/  AAS_Error (char*,...) ; 
 TYPE_2__* AAS_ReadCache (int /*<<< orphan*/ ) ; 
 scalar_t__ CRC_ProcessString (unsigned char*,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_READ ; 
 int MAX_QPATH ; 
 scalar_t__ RCID ; 
 scalar_t__ RCVERSION ; 
 TYPE_5__ aasworld ; 
 TYPE_4__ botimport ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

int AAS_ReadRouteCache(void)
{
	int i, clusterareanum;//, size;
	fileHandle_t fp;
	char filename[MAX_QPATH];
	routecacheheader_t routecacheheader;
	aas_routingcache_t *cache;

	Com_sprintf(filename, MAX_QPATH, "maps/%s.rcd", aasworld.mapname);
	botimport.FS_FOpenFile( filename, &fp, FS_READ );
	if (!fp)
	{
		return qfalse;
	} //end if
	botimport.FS_Read(&routecacheheader, sizeof(routecacheheader_t), fp );
	if (routecacheheader.ident != RCID)
	{
		AAS_Error("%s is not a route cache dump\n");
		return qfalse;
	} //end if
	if (routecacheheader.version != RCVERSION)
	{
		AAS_Error("route cache dump has wrong version %d, should be %d", routecacheheader.version, RCVERSION);
		return qfalse;
	} //end if
	if (routecacheheader.numareas != aasworld.numareas)
	{
		//AAS_Error("route cache dump has wrong number of areas\n");
		return qfalse;
	} //end if
	if (routecacheheader.numclusters != aasworld.numclusters)
	{
		//AAS_Error("route cache dump has wrong number of clusters\n");
		return qfalse;
	} //end if
	if (routecacheheader.areacrc !=
		CRC_ProcessString( (unsigned char *)aasworld.areas, sizeof(aas_area_t) * aasworld.numareas ))
	{
		//AAS_Error("route cache dump area CRC incorrect\n");
		return qfalse;
	} //end if
	if (routecacheheader.clustercrc !=
		CRC_ProcessString( (unsigned char *)aasworld.clusters, sizeof(aas_cluster_t) * aasworld.numclusters ))
	{
		//AAS_Error("route cache dump cluster CRC incorrect\n");
		return qfalse;
	} //end if
	//read all the portal cache
	for (i = 0; i < routecacheheader.numportalcache; i++)
	{
		cache = AAS_ReadCache(fp);
		cache->next = aasworld.portalcache[cache->areanum];
		cache->prev = NULL;
		if (aasworld.portalcache[cache->areanum])
			aasworld.portalcache[cache->areanum]->prev = cache;
		aasworld.portalcache[cache->areanum] = cache;
	} //end for
	//read all the cluster area cache
	for (i = 0; i < routecacheheader.numareacache; i++)
	{
		cache = AAS_ReadCache(fp);
		clusterareanum = AAS_ClusterAreaNum(cache->cluster, cache->areanum);
		cache->next = aasworld.clusterareacache[cache->cluster][clusterareanum];
		cache->prev = NULL;
		if (aasworld.clusterareacache[cache->cluster][clusterareanum])
			aasworld.clusterareacache[cache->cluster][clusterareanum]->prev = cache;
		aasworld.clusterareacache[cache->cluster][clusterareanum] = cache;
	} //end for
	// read the visareas
	/*
	aasworld.areavisibility = (byte **) GetClearedMemory(aasworld.numareas * sizeof(byte *));
	aasworld.decompressedvis = (byte *) GetClearedMemory(aasworld.numareas * sizeof(byte));
	for (i = 0; i < aasworld.numareas; i++)
	{
		botimport.FS_Read(&size, sizeof(size), fp );
		if (size) {
			aasworld.areavisibility[i] = (byte *) GetMemory(size);
			botimport.FS_Read(aasworld.areavisibility[i], size, fp );
		}
	}
	*/
	//
	botimport.FS_FCloseFile(fp);
	return qtrue;
}