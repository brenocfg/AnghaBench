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
struct TYPE_2__ {int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  mz_zip_create (int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_open (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  mz_zip_writer_close (void*) ; 

__attribute__((used)) static int32_t mz_zip_writer_open_int(void *handle, void *stream, int32_t mode)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    int32_t err = MZ_OK;

    mz_zip_create(&writer->zip_handle);
    err = mz_zip_open(writer->zip_handle, stream, mode);

    if (err != MZ_OK)
    {
        mz_zip_writer_close(handle);
        return err;
    }

    return MZ_OK;
}