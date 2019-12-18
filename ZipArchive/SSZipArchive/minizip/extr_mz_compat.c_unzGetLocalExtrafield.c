#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ unzFile ;
struct TYPE_4__ {scalar_t__ extrafield_size; int /*<<< orphan*/  extrafield; } ;
typedef  TYPE_1__ mz_zip_file ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 unsigned int INT32_MAX ; 
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mz_zip_entry_get_local_info (int /*<<< orphan*/ ,TYPE_1__**) ; 

int unzGetLocalExtrafield(unzFile file, void *buf, unsigned int len)
{
    mz_compat *compat = (mz_compat *)file;
    mz_zip_file *file_info = NULL;
    int32_t err = MZ_OK;
    int32_t bytes_to_copy = 0;

    if (compat == NULL || buf == NULL || len >= INT32_MAX)
        return UNZ_PARAMERROR;
    
    err = mz_zip_entry_get_local_info(compat->handle, &file_info);
    if (err != MZ_OK)
        return err;
    
    bytes_to_copy = (int32_t)len;
    if (bytes_to_copy > file_info->extrafield_size)
        bytes_to_copy = file_info->extrafield_size;

    memcpy(buf, file_info->extrafield, bytes_to_copy);
    return MZ_OK;
}