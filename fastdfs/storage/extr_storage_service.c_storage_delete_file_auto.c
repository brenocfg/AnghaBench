#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int file_type; int /*<<< orphan*/  trunk_info; } ;
struct TYPE_6__ {TYPE_1__ upload; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; TYPE_2__ extra_info; } ;
typedef  TYPE_3__ StorageFileContext ;

/* Variables and functions */
 int ENOENT ; 
 int _FILE_TYPE_TRUNK ; 
 scalar_t__ errno ; 
 int trunk_file_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int storage_delete_file_auto(StorageFileContext *pFileContext)
{
	if (pFileContext->extra_info.upload.file_type & _FILE_TYPE_TRUNK)
	{
		return trunk_file_delete(pFileContext->filename,
                        &(pFileContext->extra_info.upload.trunk_info));
	}
	else
	{
		if (unlink(pFileContext->filename) == 0)
		{
			return 0;
		}
		else
		{
			return errno != 0 ? errno : ENOENT;
		}
	}
}