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
struct TYPE_3__ {scalar_t__ comment_size; scalar_t__ extrafield_size; scalar_t__ filename_size; } ;
struct TYPE_4__ {TYPE_1__ file_info; int /*<<< orphan*/  cd_current_pos; } ;
typedef  TYPE_2__ mz_zip ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 scalar_t__ MZ_ZIP_SIZE_CD_ITEM ; 
 int /*<<< orphan*/  mz_zip_goto_next_entry_int (void*) ; 

int32_t mz_zip_goto_next_entry(void *handle)
{
    mz_zip *zip = (mz_zip *)handle;

    if (zip == NULL)
        return MZ_PARAM_ERROR;

    zip->cd_current_pos += (int64_t)MZ_ZIP_SIZE_CD_ITEM + zip->file_info.filename_size +
        zip->file_info.extrafield_size + zip->file_info.comment_size;

    return mz_zip_goto_next_entry_int(handle);
}