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
typedef  int /*<<< orphan*/ * unzFile ;
struct TYPE_2__ {void* handle; void* stream; } ;
typedef  TYPE_1__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_ALLOC (int) ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_READ ; 
 int /*<<< orphan*/  mz_zip_create (void**) ; 
 int /*<<< orphan*/  mz_zip_delete (void**) ; 
 int /*<<< orphan*/  mz_zip_goto_first_entry (void*) ; 
 scalar_t__ mz_zip_open (void*,void*,int /*<<< orphan*/ ) ; 

unzFile unzOpen_MZ(void *stream)
{
    mz_compat *compat = NULL;
    int32_t err = MZ_OK;
    void *handle = NULL;

    mz_zip_create(&handle);
    err = mz_zip_open(handle, stream, MZ_OPEN_MODE_READ);

    if (err != MZ_OK)
    {
        mz_zip_delete(&handle);
        return NULL;
    }

    compat = (mz_compat *)MZ_ALLOC(sizeof(mz_compat));
    if (compat != NULL)
    {
        compat->handle = handle;
        compat->stream = stream;

        mz_zip_goto_first_entry(compat->handle);
    }
    else
    {
        mz_zip_delete(&handle);
    }

    return (unzFile)compat;
}