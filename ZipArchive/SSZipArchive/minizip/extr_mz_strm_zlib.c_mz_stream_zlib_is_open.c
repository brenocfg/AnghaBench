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
struct TYPE_2__ {int initialized; } ;
typedef  TYPE_1__ mz_stream_zlib ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_ERROR ; 

int32_t mz_stream_zlib_is_open(void *stream)
{
    mz_stream_zlib *zlib = (mz_stream_zlib *)stream;
    if (zlib->initialized != 1)
        return MZ_OPEN_ERROR;
    return MZ_OK;
}