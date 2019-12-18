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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ store_links; scalar_t__ aes; scalar_t__ zip_cd; int /*<<< orphan*/  compress_method; } ;
typedef  TYPE_1__ mz_zip_writer ;
struct TYPE_6__ {char const* filename; int external_fa; char* linkname; int /*<<< orphan*/  version_madeby; int /*<<< orphan*/  creation_date; int /*<<< orphan*/  accessed_date; int /*<<< orphan*/  modified_date; int /*<<< orphan*/  aes_version; int /*<<< orphan*/  flag; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  compression_method; } ;
typedef  TYPE_2__ mz_zip_file ;
typedef  int /*<<< orphan*/  link_path ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  file_info ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_AES_VERSION ; 
 scalar_t__ MZ_HOST_SYSTEM (int /*<<< orphan*/ ) ; 
 scalar_t__ MZ_HOST_SYSTEM_MSDOS ; 
 scalar_t__ MZ_HOST_SYSTEM_WINDOWS_NTFS ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_READ ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_VERSION_MADEBY ; 
 int /*<<< orphan*/  MZ_ZIP_FLAG_MASK_LOCAL_INFO ; 
 int /*<<< orphan*/  MZ_ZIP_FLAG_UTF8 ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mz_os_get_file_attribs (char const*,int*) ; 
 int /*<<< orphan*/  mz_os_get_file_date (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_os_get_file_size (char const*) ; 
 scalar_t__ mz_os_is_dir (char const*) ; 
 scalar_t__ mz_os_is_symlink (char const*) ; 
 scalar_t__ mz_os_read_symlink (char const*,char*,int) ; 
 scalar_t__ mz_path_get_filename (char const*,char const**) ; 
 int /*<<< orphan*/  mz_stream_close (void*) ; 
 int /*<<< orphan*/  mz_stream_delete (void**) ; 
 int /*<<< orphan*/  mz_stream_os_create (void**) ; 
 scalar_t__ mz_stream_os_open (void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_read ; 
 scalar_t__ mz_zip_attrib_convert (scalar_t__,int,scalar_t__,int*) ; 
 scalar_t__ mz_zip_writer_add_info (void*,void*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ mz_zip_writer_is_open (void*) ; 

int32_t mz_zip_writer_add_file(void *handle, const char *path, const char *filename_in_zip)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    mz_zip_file file_info;
    uint32_t target_attrib = 0;
    uint32_t src_attrib = 0;
    int32_t err = MZ_OK;
    uint8_t src_sys = 0;
    void *stream = NULL;
    char link_path[1024];
    const char *filename = filename_in_zip;


    if (mz_zip_writer_is_open(handle) != MZ_OK)
        return MZ_PARAM_ERROR;
    if (path == NULL)
        return MZ_PARAM_ERROR;

    if (filename == NULL)
    {
        err = mz_path_get_filename(path, &filename);
        if (err != MZ_OK)
            return err;
    }

    memset(&file_info, 0, sizeof(file_info));

    /* The path name saved, should not include a leading slash. */
    /* If it did, windows/xp and dynazip couldn't read the zip file. */

    while (filename[0] == '\\' || filename[0] == '/')
        filename += 1;

    /* Get information about the file on disk so we can store it in zip */

    file_info.version_madeby = MZ_VERSION_MADEBY;
    file_info.compression_method = writer->compress_method;
    file_info.filename = filename;
    file_info.uncompressed_size = mz_os_get_file_size(path);
    file_info.flag = MZ_ZIP_FLAG_UTF8;

    if (writer->zip_cd)
        file_info.flag |= MZ_ZIP_FLAG_MASK_LOCAL_INFO;
    if (writer->aes)
        file_info.aes_version = MZ_AES_VERSION;

    mz_os_get_file_date(path, &file_info.modified_date, &file_info.accessed_date,
        &file_info.creation_date);
    mz_os_get_file_attribs(path, &src_attrib);

    src_sys = MZ_HOST_SYSTEM(file_info.version_madeby);

    if ((src_sys != MZ_HOST_SYSTEM_MSDOS) && (src_sys != MZ_HOST_SYSTEM_WINDOWS_NTFS))
    {
        /* High bytes are OS specific attributes, low byte is always DOS attributes */
        if (mz_zip_attrib_convert(src_sys, src_attrib, MZ_HOST_SYSTEM_MSDOS, &target_attrib) == MZ_OK)
            file_info.external_fa = target_attrib;
        file_info.external_fa |= (src_attrib << 16);
    }
    else
    {
        file_info.external_fa = src_attrib;
    }

    if (writer->store_links && mz_os_is_symlink(path) == MZ_OK)
    {
        err = mz_os_read_symlink(path, link_path, sizeof(link_path));
        if (err == MZ_OK)
            file_info.linkname = link_path;
    }

    if (mz_os_is_dir(path) != MZ_OK)
    {
        mz_stream_os_create(&stream);
        err = mz_stream_os_open(stream, path, MZ_OPEN_MODE_READ);
    }

    if (err == MZ_OK)
        err = mz_zip_writer_add_info(handle, stream, mz_stream_read, &file_info);

    if (stream != NULL)
    {
        mz_stream_close(stream);
        mz_stream_delete(&stream);
    }

    return err;
}