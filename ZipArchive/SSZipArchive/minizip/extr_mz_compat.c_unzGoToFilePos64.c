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
struct TYPE_4__ {int /*<<< orphan*/  num_of_file; int /*<<< orphan*/  pos_in_zip_directory; } ;
typedef  TYPE_1__ unz64_file_pos ;
struct TYPE_5__ {int /*<<< orphan*/  entry_index; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 scalar_t__ mz_zip_goto_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int unzGoToFilePos64(unzFile file, const unz64_file_pos *file_pos)
{
    mz_compat *compat = (mz_compat *)file;
    int32_t err = MZ_OK;

    if (compat == NULL || file_pos == NULL)
        return UNZ_PARAMERROR;

    err = mz_zip_goto_entry(compat->handle, file_pos->pos_in_zip_directory);
    if (err == MZ_OK)
        compat->entry_index = file_pos->num_of_file;
    return err;
}