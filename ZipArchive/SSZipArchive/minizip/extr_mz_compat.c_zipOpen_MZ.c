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
typedef  int /*<<< orphan*/ * zipFile ;
struct TYPE_2__ {void* stream; void* handle; } ;
typedef  TYPE_1__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_ALLOC (int) ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  mz_zip_create (void**) ; 
 int /*<<< orphan*/  mz_zip_delete (void**) ; 
 int /*<<< orphan*/  mz_zip_get_comment (void*,char const**) ; 
 scalar_t__ mz_zip_open (void*,void*,scalar_t__) ; 
 scalar_t__ zipConvertAppendToStreamMode (int) ; 

zipFile zipOpen_MZ(void *stream, int append, const char **globalcomment)
{
    mz_compat *compat = NULL;
    int32_t err = MZ_OK;
    int32_t mode = zipConvertAppendToStreamMode(append);
    void *handle = NULL;

    mz_zip_create(&handle);
    err = mz_zip_open(handle, stream, mode);

    if (err != MZ_OK)
    {
        mz_zip_delete(&handle);
        return NULL;
    }

    if (globalcomment != NULL)
        mz_zip_get_comment(handle, globalcomment);

    compat = (mz_compat *)MZ_ALLOC(sizeof(mz_compat));
    if (compat != NULL)
    {
        compat->handle = handle;
        compat->stream = stream;
    }
    else
    {
        mz_zip_delete(&handle);
    }

    return (zipFile)compat;
}