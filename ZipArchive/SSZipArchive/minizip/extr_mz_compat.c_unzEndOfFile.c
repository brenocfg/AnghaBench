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
struct TYPE_4__ {scalar_t__ uncompressed_size; } ;
typedef  TYPE_1__ mz_zip_file ;
struct TYPE_5__ {scalar_t__ total_out; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ mz_compat ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 scalar_t__ mz_zip_entry_get_info (int /*<<< orphan*/ ,TYPE_1__**) ; 

int unzEndOfFile(unzFile file)
{
    mz_compat *compat = (mz_compat *)file;
    mz_zip_file *file_info = NULL;
    int32_t err = MZ_OK;

    if (compat == NULL)
        return UNZ_PARAMERROR;
    err = mz_zip_entry_get_info(compat->handle, &file_info);
    if (err != MZ_OK)
        return err;
    if (compat->total_out == (int64_t)file_info->uncompressed_size)
        return 1;
    return 0;
}