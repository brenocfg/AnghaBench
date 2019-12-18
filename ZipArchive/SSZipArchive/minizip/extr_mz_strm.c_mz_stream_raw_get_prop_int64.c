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
struct TYPE_2__ {int /*<<< orphan*/  total_out; int /*<<< orphan*/  total_in; } ;
typedef  TYPE_1__ mz_stream_raw ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_EXIST_ERROR ; 
 int MZ_OK ; 
#define  MZ_STREAM_PROP_TOTAL_IN 129 
#define  MZ_STREAM_PROP_TOTAL_OUT 128 

int32_t mz_stream_raw_get_prop_int64(void *stream, int32_t prop, int64_t *value)
{
    mz_stream_raw *raw = (mz_stream_raw *)stream;
    switch (prop)
    {
    case MZ_STREAM_PROP_TOTAL_IN:
        *value = raw->total_in;
        return MZ_OK;
    case MZ_STREAM_PROP_TOTAL_OUT:
        *value = raw->total_out;
        return MZ_OK;
    }
    return MZ_EXIST_ERROR;
}