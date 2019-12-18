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
struct TYPE_3__ {int const bytes; } ;
typedef  TYPE_1__ TestFileInfo ;

/* Variables and functions */
 int FILE_TYPE_COUNT ; 
 TYPE_1__* files ; 

__attribute__((used)) static int get_file_type_index(const int file_bytes)
{
	TestFileInfo *pFile;
	TestFileInfo *pEnd;

	pEnd = files + FILE_TYPE_COUNT;
	for (pFile=files; pFile<pEnd; pFile++)
	{
		if (file_bytes == pFile->bytes)
		{
			return pFile - files;
		}
	}

	return -1;
}