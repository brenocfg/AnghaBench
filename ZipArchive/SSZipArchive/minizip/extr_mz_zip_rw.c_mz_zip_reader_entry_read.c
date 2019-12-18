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
struct TYPE_2__ {int /*<<< orphan*/ * hash; int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mz_crypt_sha_update (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ mz_zip_entry_read (int /*<<< orphan*/ ,void*,scalar_t__) ; 

int32_t mz_zip_reader_entry_read(void *handle, void *buf, int32_t len)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t read = 0;
    read = mz_zip_entry_read(reader->zip_handle, buf, len);
#ifndef MZ_ZIP_NO_ENCRYPTION
    if ((read > 0) && (reader->hash != NULL))
        mz_crypt_sha_update(reader->hash, buf, read);
#endif
    return read;
}