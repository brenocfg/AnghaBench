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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int int64 ;

/* Variables and functions */
 char* QueryResultFileName (char*) ; 
 int stat (char*,struct stat*) ; 

int64
IntermediateResultSize(char *resultId)
{
	char *resultFileName = NULL;
	struct stat fileStat;
	int statOK = 0;

	resultFileName = QueryResultFileName(resultId);
	statOK = stat(resultFileName, &fileStat);
	if (statOK < 0)
	{
		return -1;
	}

	return (int64) fileStat.st_size;
}