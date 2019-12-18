#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mz_dos_date; int /*<<< orphan*/  internal_fa; int /*<<< orphan*/  external_fa; int /*<<< orphan*/  tmz_date; } ;
typedef  TYPE_1__ zip_fileinfo ;
typedef  scalar_t__ zipFile ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  void const* uint16_t ;
struct TYPE_8__ {char const* filename; char const* comment; int flag; int /*<<< orphan*/  aes_version; int /*<<< orphan*/  zip64; void const* version_madeby; void const* extrafield_size; void const* extrafield; void const* compression_method; int /*<<< orphan*/  internal_fa; int /*<<< orphan*/  external_fa; int /*<<< orphan*/  modified_date; } ;
typedef  TYPE_2__ mz_zip_file ;
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ mz_compat ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  file_info ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_AES_VERSION ; 
 int /*<<< orphan*/  MZ_UNUSED (void const*) ; 
 int /*<<< orphan*/  MZ_ZIP64_DISABLE ; 
 int /*<<< orphan*/  MZ_ZIP64_FORCE ; 
 int MZ_ZIP_FLAG_ENCRYPTED ; 
 int ZIP_PARAMERROR ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mz_zip_dosdate_to_time_t (scalar_t__) ; 
 int mz_zip_entry_write_open (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ mz_zip_tm_to_dosdate (int /*<<< orphan*/ *) ; 

int zipOpenNewFileInZip5(zipFile file, const char *filename, const zip_fileinfo *zipfi,
    const void *extrafield_local, uint16_t size_extrafield_local, const void *extrafield_global,
    uint16_t size_extrafield_global, const char *comment, uint16_t compression_method, int level,
    int raw, int windowBits, int memLevel, int strategy, const char *password,
    signed char aes, uint16_t version_madeby, uint16_t flag_base, int zip64)
{
    mz_compat *compat = (mz_compat *)file;
    mz_zip_file file_info;
    uint64_t dos_date = 0;

    MZ_UNUSED(strategy);
    MZ_UNUSED(memLevel);
    MZ_UNUSED(windowBits);
    MZ_UNUSED(size_extrafield_local);
    MZ_UNUSED(extrafield_local);

    if (compat == NULL)
        return ZIP_PARAMERROR;

    memset(&file_info, 0, sizeof(file_info));

    if (zipfi != NULL)
    {
        if (zipfi->mz_dos_date != 0)
            dos_date = zipfi->mz_dos_date;
        else
            dos_date = mz_zip_tm_to_dosdate(&zipfi->tmz_date);

        file_info.modified_date = mz_zip_dosdate_to_time_t(dos_date);
        file_info.external_fa = zipfi->external_fa;
        file_info.internal_fa = zipfi->internal_fa;
    }

    if (filename == NULL)
        filename = "-";

    file_info.compression_method = compression_method;
    file_info.filename = filename;
    /* file_info.extrafield_local = extrafield_local; */
    /* file_info.extrafield_local_size = size_extrafield_local; */
    file_info.extrafield = extrafield_global;
    file_info.extrafield_size = size_extrafield_global;
    file_info.version_madeby = version_madeby;
    file_info.comment = comment;
    file_info.flag = flag_base;
    if (zip64)
        file_info.zip64 = MZ_ZIP64_FORCE;
    else
        file_info.zip64 = MZ_ZIP64_DISABLE;
#ifdef HAVE_WZAES
    if ((aes && password != NULL) || (raw && (file_info.flag & MZ_ZIP_FLAG_ENCRYPTED)))
        file_info.aes_version = MZ_AES_VERSION;
#endif

    return mz_zip_entry_write_open(compat->handle, &file_info, (int16_t)level, (uint8_t)raw, password);
}