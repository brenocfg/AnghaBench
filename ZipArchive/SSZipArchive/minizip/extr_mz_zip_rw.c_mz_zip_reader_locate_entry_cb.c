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
struct TYPE_4__ {int /*<<< orphan*/  pattern_ignore_case; int /*<<< orphan*/  pattern; } ;
typedef  TYPE_1__ mz_zip_reader ;
struct TYPE_5__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ mz_zip_file ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_UNUSED (void*) ; 
 int /*<<< orphan*/  mz_path_compare_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t mz_zip_reader_locate_entry_cb(void *handle, void *userdata, mz_zip_file *file_info)
{
    mz_zip_reader *reader = (mz_zip_reader *)userdata;
    int32_t result = 0;
    MZ_UNUSED(handle);
    result = mz_path_compare_wc(file_info->filename, reader->pattern, reader->pattern_ignore_case);
    return result;
}