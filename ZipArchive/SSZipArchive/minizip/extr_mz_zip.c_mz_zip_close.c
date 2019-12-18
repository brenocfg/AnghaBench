#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int open_mode; int /*<<< orphan*/ * cd_stream; int /*<<< orphan*/ * stream; int /*<<< orphan*/ * comment; int /*<<< orphan*/ * local_file_info_stream; int /*<<< orphan*/ * file_info_stream; int /*<<< orphan*/ * cd_mem_stream; } ;
typedef  TYPE_1__ mz_zip ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ MZ_OK ; 
 int MZ_OPEN_MODE_WRITE ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_mem_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (int /*<<< orphan*/ **) ; 
 scalar_t__ mz_zip_entry_close (void*) ; 
 scalar_t__ mz_zip_entry_is_open (void*) ; 
 int /*<<< orphan*/  mz_zip_print (char*) ; 
 scalar_t__ mz_zip_write_cd (void*) ; 

int32_t mz_zip_close(void *handle)
{
    mz_zip *zip = (mz_zip *)handle;
    int32_t err = MZ_OK;

    if (zip == NULL)
        return MZ_PARAM_ERROR;

    mz_zip_print("Zip - Close\n");

    if (mz_zip_entry_is_open(handle) == MZ_OK)
        err = mz_zip_entry_close(handle);

    if ((err == MZ_OK) && (zip->open_mode & MZ_OPEN_MODE_WRITE))
        err = mz_zip_write_cd(handle);

    if (zip->cd_mem_stream != NULL)
    {
        mz_stream_close(zip->cd_mem_stream);
        mz_stream_delete(&zip->cd_mem_stream);
    }

    if (zip->file_info_stream != NULL)
    {
        mz_stream_mem_close(zip->file_info_stream);
        mz_stream_mem_delete(&zip->file_info_stream);
    }
    if (zip->local_file_info_stream != NULL)
    {
        mz_stream_mem_close(zip->local_file_info_stream);
        mz_stream_mem_delete(&zip->local_file_info_stream);
    }

    if (zip->comment)
    {
        MZ_FREE(zip->comment);
        zip->comment = NULL;
    }

    zip->stream = NULL;
    zip->cd_stream = NULL;

    return err;
}