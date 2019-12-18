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
typedef  scalar_t__ zipFile ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ INT32_MAX ; 
 int ZIP_ERRNO ; 
 int ZIP_OK ; 
 int ZIP_PARAMERROR ; 
 scalar_t__ mz_zip_entry_write (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

int zipWriteInFileInZip(zipFile file, const void *buf, uint32_t len)
{
    mz_compat *compat = (mz_compat *)file;
    int32_t written = 0;
    if (compat == NULL || len >= INT32_MAX)
        return ZIP_PARAMERROR;
    written = mz_zip_entry_write(compat->handle, buf, (int32_t)len);
    if ((written < 0) || ((uint32_t)written != len))
        return ZIP_ERRNO;
    return ZIP_OK;
}