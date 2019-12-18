#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* file_info; int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_2__ mz_zip_reader ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  extrafield_size; int /*<<< orphan*/  extrafield; } ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_ZIP_EXTENSION_SIGN ; 
 scalar_t__ mz_zip_entry_is_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_extrafield_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32_t mz_zip_reader_entry_has_sign(void *handle)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;

    if (reader == NULL || mz_zip_entry_is_open(reader->zip_handle) != MZ_OK)
        return MZ_PARAM_ERROR;

    return mz_zip_extrafield_contains(reader->file_info->extrafield,
        reader->file_info->extrafield_size, MZ_ZIP_EXTENSION_SIGN, NULL);
}