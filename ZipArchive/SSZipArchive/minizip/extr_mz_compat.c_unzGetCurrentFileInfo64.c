#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size_filename; scalar_t__ size_file_extra; scalar_t__ size_file_comment; void* uncompressed_size; void* compressed_size; int /*<<< orphan*/  external_fa; int /*<<< orphan*/  internal_fa; int /*<<< orphan*/  disk_num_start; int /*<<< orphan*/  crc; int /*<<< orphan*/  mz_dos_date; int /*<<< orphan*/  compression_method; int /*<<< orphan*/  flag; int /*<<< orphan*/  version_needed; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ unz_file_info64 ;
typedef  scalar_t__ unzFile ;
typedef  void* uint64_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_7__ {scalar_t__ filename_size; scalar_t__ extrafield_size; scalar_t__ comment_size; int /*<<< orphan*/ * comment; int /*<<< orphan*/  extrafield; int /*<<< orphan*/ * filename; scalar_t__ uncompressed_size; scalar_t__ compressed_size; int /*<<< orphan*/  external_fa; int /*<<< orphan*/  internal_fa; int /*<<< orphan*/  disk_number; int /*<<< orphan*/  crc; int /*<<< orphan*/  modified_date; int /*<<< orphan*/  compression_method; int /*<<< orphan*/  flag; int /*<<< orphan*/  version_needed; int /*<<< orphan*/  version_madeby; } ;
typedef  TYPE_2__ mz_zip_file ;
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mz_zip_entry_get_info (int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  mz_zip_time_t_to_dos_date (int /*<<< orphan*/ ) ; 

int unzGetCurrentFileInfo64(unzFile file, unz_file_info64 * pfile_info, char *filename,
    uint16_t filename_size, void *extrafield, uint16_t extrafield_size, char *comment, uint16_t comment_size)
{
    mz_compat *compat = (mz_compat *)file;
    mz_zip_file *file_info = NULL;
    uint16_t bytes_to_copy = 0;
    int32_t err = MZ_OK;

    if (compat == NULL)
        return UNZ_PARAMERROR;

    err = mz_zip_entry_get_info(compat->handle, &file_info);

    if ((err == MZ_OK) && (pfile_info != NULL))
    {
        pfile_info->version = file_info->version_madeby;
        pfile_info->version_needed = file_info->version_needed;
        pfile_info->flag = file_info->flag;
        pfile_info->compression_method = file_info->compression_method;
        pfile_info->mz_dos_date = mz_zip_time_t_to_dos_date(file_info->modified_date);
        //mz_zip_time_t_to_tm(file_info->modified_date, &pfile_info->tmu_date);
        //pfile_info->tmu_date.tm_year += 1900;
        pfile_info->crc = file_info->crc;

        pfile_info->size_filename = file_info->filename_size;
        pfile_info->size_file_extra = file_info->extrafield_size;
        pfile_info->size_file_comment = file_info->comment_size;

        pfile_info->disk_num_start = file_info->disk_number;
        pfile_info->internal_fa = file_info->internal_fa;
        pfile_info->external_fa = file_info->external_fa;

        pfile_info->compressed_size = (uint64_t)file_info->compressed_size;
        pfile_info->uncompressed_size = (uint64_t)file_info->uncompressed_size;

        if (filename_size > 0 && filename != NULL && file_info->filename != NULL)
        {
            bytes_to_copy = filename_size;
            if (bytes_to_copy > file_info->filename_size)
                bytes_to_copy = file_info->filename_size;
            memcpy(filename, file_info->filename, bytes_to_copy);
            if (bytes_to_copy < filename_size)
                filename[bytes_to_copy] = 0;
        }

        if (extrafield_size > 0 && extrafield != NULL)
        {
            bytes_to_copy = extrafield_size;
            if (bytes_to_copy > file_info->extrafield_size)
                bytes_to_copy = file_info->extrafield_size;
            memcpy(extrafield, file_info->extrafield, bytes_to_copy);
        }

        if (comment_size > 0 && comment != NULL && file_info->comment != NULL)
        {
            bytes_to_copy = comment_size;
            if (bytes_to_copy > file_info->comment_size)
                bytes_to_copy = file_info->comment_size;
            memcpy(comment, file_info->comment, bytes_to_copy);
            if (bytes_to_copy < comment_size)
                comment[bytes_to_copy] = 0;
        }
    }
    return err;
}