#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* FS_Read ) (char*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* FS_FCloseFile ) (int /*<<< orphan*/ ) ;scalar_t__ (* FS_Seek ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_DumpAASData () ; 
 int /*<<< orphan*/  AAS_Error (char*) ; 
 int /*<<< orphan*/  FS_SEEK_SET ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 int /*<<< orphan*/  PRT_WARNING ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*,int,int /*<<< orphan*/ ) ; 

char *AAS_LoadAASLump(fileHandle_t fp, int offset, int length, int *lastoffset, int size)
{
	char *buf;
	//
	if (!length)
	{
		//just alloc a dummy
		return (char *) GetClearedHunkMemory(size+1);
	} //end if
	//seek to the data
	if (offset != *lastoffset)
	{
		botimport.Print(PRT_WARNING, "AAS file not sequentially read\n");
		if (botimport.FS_Seek(fp, offset, FS_SEEK_SET))
		{
			AAS_Error("can't seek to aas lump\n");
			AAS_DumpAASData();
			botimport.FS_FCloseFile(fp);
			return 0;
		} //end if
	} //end if
	//allocate memory
	buf = (char *) GetClearedHunkMemory(length+1);
	//read the data
	if (length)
	{
		botimport.FS_Read(buf, length, fp );
		*lastoffset += length;
	} //end if
	return buf;
}