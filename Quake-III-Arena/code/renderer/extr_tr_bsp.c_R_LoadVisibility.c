#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int filelen; int fileofs; } ;
typedef  TYPE_1__ lump_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_9__ {int /*<<< orphan*/ * (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int numClusters; int /*<<< orphan*/ * vis; void* clusterBytes; int /*<<< orphan*/ * novis; } ;
struct TYPE_7__ {int /*<<< orphan*/ * externalVisData; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int,int) ; 
 void* LittleLong (int) ; 
 int /*<<< orphan*/ * fileBase ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_4__ ri ; 
 TYPE_3__ s_worldData ; 
 int /*<<< orphan*/ * stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ tr ; 

__attribute__((used)) static	void R_LoadVisibility( lump_t *l ) {
	int		len;
	byte	*buf;

	len = ( s_worldData.numClusters + 63 ) & ~63;
	s_worldData.novis = ri.Hunk_Alloc( len, h_low );
	Com_Memset( s_worldData.novis, 0xff, len );

    len = l->filelen;
	if ( !len ) {
		return;
	}
	buf = fileBase + l->fileofs;

	s_worldData.numClusters = LittleLong( ((int *)buf)[0] );
	s_worldData.clusterBytes = LittleLong( ((int *)buf)[1] );

	// CM_Load should have given us the vis data to share, so
	// we don't need to allocate another copy
	if ( tr.externalVisData ) {
		s_worldData.vis = tr.externalVisData;
	} else {
		byte	*dest;

		dest = ri.Hunk_Alloc( len - 8, h_low );
		Com_Memcpy( dest, buf + 8, len - 8 );
		s_worldData.vis = dest;
	}
}