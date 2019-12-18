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
struct TYPE_3__ {int file_type; int alloc_size; int file_size; int crc32; int mtime; char* formatted_ext_name; } ;
typedef  TYPE_1__ FDFSTrunkHeader ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int const,char*,int,int,int,int,int,int,char*) ; 
 scalar_t__ strlen (char*) ; 

char *trunk_header_dump(const FDFSTrunkHeader *pTrunkHeader, char *buff, \
				const int buff_size)
{
	snprintf(buff, buff_size, \
		"file_type=%d, " \
		"alloc_size=%d, " \
		"file_size=%d, " \
		"crc32=%d, " \
		"mtime=%d, " \
		"ext_name(%d)=%s", \
		pTrunkHeader->file_type, pTrunkHeader->alloc_size, \
		pTrunkHeader->file_size, pTrunkHeader->crc32, \
		pTrunkHeader->mtime, \
		(int)strlen(pTrunkHeader->formatted_ext_name), \
		pTrunkHeader->formatted_ext_name);

	return buff;
}