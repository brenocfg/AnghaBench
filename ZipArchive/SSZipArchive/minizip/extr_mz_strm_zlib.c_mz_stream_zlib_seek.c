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
typedef  void* int64_t ;
typedef  void* int32_t ;

/* Variables and functions */
 void* MZ_SEEK_ERROR ; 
 int /*<<< orphan*/  MZ_UNUSED (void*) ; 

int32_t mz_stream_zlib_seek(void *stream, int64_t offset, int32_t origin)
{
    MZ_UNUSED(stream);
    MZ_UNUSED(offset);
    MZ_UNUSED(origin);

    return MZ_SEEK_ERROR;
}