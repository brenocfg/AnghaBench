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
typedef  int /*<<< orphan*/  fileHandle_t ;

/* Variables and functions */
 int FGetLittleLong (int /*<<< orphan*/ ) ; 
 int FS_Read (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

int S_FindWavChunk( fileHandle_t f, char *chunk ) {
	char	name[5];
	int		len;
	int		r;

	name[4] = 0;
	len = 0;
	r = FS_Read( name, 4, f );
	if ( r != 4 ) {
		return 0;
	}
	len = FGetLittleLong( f );
	if ( len < 0 || len > 0xfffffff ) {
		len = 0;
		return 0;
	}
	len = (len + 1 ) & ~1;		// pad to word boundary
//	s_nextWavChunk += len + 8;

	if ( strcmp( name, chunk ) ) {
		return 0;
	}

	return len;
}