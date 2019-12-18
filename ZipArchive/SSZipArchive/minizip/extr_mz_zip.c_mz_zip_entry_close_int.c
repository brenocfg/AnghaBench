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
struct TYPE_2__ {scalar_t__ entry_opened; int /*<<< orphan*/ * compress_stream; int /*<<< orphan*/ * crypt_stream; } ;
typedef  TYPE_1__ mz_zip ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  mz_stream_delete (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int32_t mz_zip_entry_close_int(void *handle)
{
    mz_zip *zip = (mz_zip *)handle;

    if (zip->crypt_stream != NULL)
        mz_stream_delete(&zip->crypt_stream);
    zip->crypt_stream = NULL;
    if (zip->compress_stream != NULL)
        mz_stream_delete(&zip->compress_stream);
    zip->compress_stream = NULL;

    zip->entry_opened = 0;

    return MZ_OK;
}