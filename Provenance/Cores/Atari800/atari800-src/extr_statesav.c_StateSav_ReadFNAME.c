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
typedef  size_t UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 size_t FILENAME_MAX ; 
 int /*<<< orphan*/  Log_print (char*,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  StateSav_ReadUWORD (size_t*,int) ; 

void StateSav_ReadFNAME(char *filename)
{
	UWORD namelen = 0;

	StateSav_ReadUWORD(&namelen, 1);
	if (namelen >= FILENAME_MAX) {
		Log_print("Filenames of %d characters not supported on this platform", (int) namelen);
		return;
	}
	StateSav_ReadUBYTE((UBYTE *) filename, namelen);
	filename[namelen] = 0;
}