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
typedef  int /*<<< orphan*/  ZIP_PACKER ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  ZipAddFileData (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ZipAddFileStart (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void ZipAddFileSimple(ZIP_PACKER *p, char *name, UINT64 dt, UINT attribute, void *data, UINT size)
{
	// Validate arguments
	if (p == NULL || IsEmptyStr(name) || (size != 0 && data == NULL))
	{
		return;
	}

	ZipAddFileStart(p, name, size, dt, attribute);
	ZipAddFileData(p, data, 0, size);
}