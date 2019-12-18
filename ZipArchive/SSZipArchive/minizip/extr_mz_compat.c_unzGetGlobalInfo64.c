#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  number_disk_with_CD; int /*<<< orphan*/  number_entry; scalar_t__ size_comment; } ;
typedef  TYPE_1__ unz_global_info64 ;
typedef  scalar_t__ unzFile ;
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_EXIST_ERROR ; 
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mz_zip_get_comment (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ mz_zip_get_disk_number_with_cd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_get_number_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

int unzGetGlobalInfo64(unzFile file, unz_global_info64 *pglobal_info)
{
    mz_compat *compat = (mz_compat *)file;
    const char *comment_ptr = NULL;
    int32_t err = MZ_OK;

    memset(pglobal_info, 0, sizeof(unz_global_info64));
    if (compat == NULL)
        return UNZ_PARAMERROR;
    err = mz_zip_get_comment(compat->handle, &comment_ptr);
    if (err == MZ_OK)
        pglobal_info->size_comment = (uint16_t)strlen(comment_ptr);
    if ((err == MZ_OK) || (err == MZ_EXIST_ERROR))
        err = mz_zip_get_number_entry(compat->handle, &pglobal_info->number_entry);
    if (err == MZ_OK)
        err = mz_zip_get_disk_number_with_cd(compat->handle, &pglobal_info->number_disk_with_CD);
    return err;
}