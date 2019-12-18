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
struct TYPE_2__ {int window_bits; int /*<<< orphan*/  max_total_in; int /*<<< orphan*/  level; } ;
typedef  TYPE_1__ mz_stream_zlib ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int MZ_EXIST_ERROR ; 
 int MZ_OK ; 
#define  MZ_STREAM_PROP_COMPRESS_LEVEL 130 
#define  MZ_STREAM_PROP_COMPRESS_WINDOW 129 
#define  MZ_STREAM_PROP_TOTAL_IN_MAX 128 

int32_t mz_stream_zlib_set_prop_int64(void *stream, int32_t prop, int64_t value)
{
    mz_stream_zlib *zlib = (mz_stream_zlib *)stream;
    switch (prop)
    {
    case MZ_STREAM_PROP_COMPRESS_LEVEL:
        zlib->level = (int16_t)value;
        break;
    case MZ_STREAM_PROP_TOTAL_IN_MAX:
        zlib->max_total_in = value;
        break;
    case MZ_STREAM_PROP_COMPRESS_WINDOW:
        zlib->window_bits = (int32_t)value;
        break;
    default:
        return MZ_EXIST_ERROR;
    }
    return MZ_OK;
}