#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ zlib_filefunc64_def ;
typedef  int /*<<< orphan*/ * zipFile ;
typedef  int /*<<< orphan*/  mz_stream_vtbl ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/ * mz_stream_create (void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_delete (void**) ; 
 scalar_t__ mz_stream_open (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mz_stream_os_create (void**) ; 
 int /*<<< orphan*/  zipConvertAppendToStreamMode (int) ; 
 int /*<<< orphan*/ * zipOpen_MZ (void*,int,char const**) ; 

zipFile zipOpen2_64(const void *path, int append, const char **globalcomment,
    zlib_filefunc64_def *pzlib_filefunc_def)
{
    zipFile zip = NULL;
    int32_t mode = zipConvertAppendToStreamMode(append);
    void *stream = NULL;

    if (pzlib_filefunc_def)
    {
        if (mz_stream_create(&stream, (mz_stream_vtbl *)*pzlib_filefunc_def) == NULL)
            return NULL;
    }
    else
    {
        if (mz_stream_os_create(&stream) == NULL)
            return NULL;
    }

    if (mz_stream_open(stream, path, mode) != MZ_OK)
    {
        mz_stream_delete(&stream);
        return NULL;
    }

    zip = zipOpen_MZ(stream, append, globalcomment);

    if (zip == NULL)
    {
        mz_stream_delete(&stream);
        return NULL;
    }

    return zip;
}