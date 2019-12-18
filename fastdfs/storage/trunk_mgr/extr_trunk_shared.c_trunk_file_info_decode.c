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
struct TYPE_3__ {void* size; void* offset; void* id; } ;
typedef  TYPE_1__ FDFSTrunkFileInfo ;

/* Variables and functions */
 int FDFS_TRUNK_FILE_INFO_LEN ; 
 int /*<<< orphan*/  base64_decode_auto (int /*<<< orphan*/ *,char const*,int,char*,int*) ; 
 void* buff2int (char*) ; 
 int /*<<< orphan*/  g_fdfs_base64_context ; 

void trunk_file_info_decode(const char *str, FDFSTrunkFileInfo *pTrunkFile)
{
	char buff[FDFS_TRUNK_FILE_INFO_LEN];
	int len;

	base64_decode_auto(&g_fdfs_base64_context, str, FDFS_TRUNK_FILE_INFO_LEN, \
		buff, &len);

	pTrunkFile->id = buff2int(buff);
	pTrunkFile->offset = buff2int(buff + sizeof(int));
	pTrunkFile->size = buff2int(buff + sizeof(int) * 2);
}