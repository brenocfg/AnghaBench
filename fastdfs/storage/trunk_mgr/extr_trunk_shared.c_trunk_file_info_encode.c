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
typedef  int /*<<< orphan*/  buff ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ FDFSTrunkFileInfo ;

/* Variables and functions */
 int /*<<< orphan*/  base64_encode_ex (int /*<<< orphan*/ *,char*,int,char*,int*,int) ; 
 int /*<<< orphan*/  g_fdfs_base64_context ; 
 int /*<<< orphan*/  int2buff (int /*<<< orphan*/ ,char*) ; 

void trunk_file_info_encode(const FDFSTrunkFileInfo *pTrunkFile, char *str)
{
	char buff[sizeof(int) * 3];
	int len;

	int2buff(pTrunkFile->id, buff);
	int2buff(pTrunkFile->offset, buff + sizeof(int));
	int2buff(pTrunkFile->size, buff + sizeof(int) * 2);
	base64_encode_ex(&g_fdfs_base64_context, buff, sizeof(buff), \
			str, &len, false);
}