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
struct TYPE_2__ {int /*<<< orphan*/ * sha256; int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mz_crypt_sha_update (int /*<<< orphan*/ *,void const*,scalar_t__) ; 
 scalar_t__ mz_zip_entry_write (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

int32_t mz_zip_writer_entry_write(void *handle, const void *buf, int32_t len)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    int32_t written = 0;
    written = mz_zip_entry_write(writer->zip_handle, buf, len);
#ifndef MZ_ZIP_NO_ENCRYPTION
    if ((written > 0) && (writer->sha256 != NULL))
        mz_crypt_sha_update(writer->sha256, buf, written);
#endif
    return written;
}