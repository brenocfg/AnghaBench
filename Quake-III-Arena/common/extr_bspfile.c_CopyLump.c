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
struct TYPE_5__ {TYPE_1__* lumps; } ;
typedef  TYPE_2__ dheader_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int filelen; int fileofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

int CopyLump( dheader_t	*header, int lump, void *dest, int size ) {
	int		length, ofs;

	length = header->lumps[lump].filelen;
	ofs = header->lumps[lump].fileofs;
	
	if ( length % size ) {
		Error ("LoadBSPFile: odd lump size");
	}

	memcpy( dest, (byte *)header + ofs, length );

	return length / size;
}