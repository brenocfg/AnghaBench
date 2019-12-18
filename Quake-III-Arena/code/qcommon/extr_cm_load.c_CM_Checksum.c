#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lumps; } ;
typedef  TYPE_1__ dheader_t ;

/* Variables and functions */
 unsigned int CM_LumpChecksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_BlockChecksum (unsigned int*,int) ; 
 size_t LUMP_BRUSHES ; 
 size_t LUMP_BRUSHSIDES ; 
 size_t LUMP_DRAWVERTS ; 
 size_t LUMP_LEAFBRUSHES ; 
 size_t LUMP_LEAFS ; 
 size_t LUMP_LEAFSURFACES ; 
 size_t LUMP_MODELS ; 
 size_t LUMP_NODES ; 
 size_t LUMP_PLANES ; 
 size_t LUMP_SHADERS ; 
 size_t LUMP_SURFACES ; 
 int LittleLong (int /*<<< orphan*/ ) ; 

unsigned CM_Checksum(dheader_t *header) {
	unsigned checksums[16];
	checksums[0] = CM_LumpChecksum(&header->lumps[LUMP_SHADERS]);
	checksums[1] = CM_LumpChecksum(&header->lumps[LUMP_LEAFS]);
	checksums[2] = CM_LumpChecksum(&header->lumps[LUMP_LEAFBRUSHES]);
	checksums[3] = CM_LumpChecksum(&header->lumps[LUMP_LEAFSURFACES]);
	checksums[4] = CM_LumpChecksum(&header->lumps[LUMP_PLANES]);
	checksums[5] = CM_LumpChecksum(&header->lumps[LUMP_BRUSHSIDES]);
	checksums[6] = CM_LumpChecksum(&header->lumps[LUMP_BRUSHES]);
	checksums[7] = CM_LumpChecksum(&header->lumps[LUMP_MODELS]);
	checksums[8] = CM_LumpChecksum(&header->lumps[LUMP_NODES]);
	checksums[9] = CM_LumpChecksum(&header->lumps[LUMP_SURFACES]);
	checksums[10] = CM_LumpChecksum(&header->lumps[LUMP_DRAWVERTS]);

	return LittleLong(Com_BlockChecksum(checksums, 11 * 4));
}