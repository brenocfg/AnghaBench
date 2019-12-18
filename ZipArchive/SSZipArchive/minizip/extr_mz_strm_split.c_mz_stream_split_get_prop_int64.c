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
struct TYPE_2__ {int /*<<< orphan*/  disk_size; int /*<<< orphan*/  number_disk; int /*<<< orphan*/  total_out; } ;
typedef  TYPE_1__ mz_stream_split ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_EXIST_ERROR ; 
 int MZ_OK ; 
#define  MZ_STREAM_PROP_DISK_NUMBER 130 
#define  MZ_STREAM_PROP_DISK_SIZE 129 
#define  MZ_STREAM_PROP_TOTAL_OUT 128 

int32_t mz_stream_split_get_prop_int64(void *stream, int32_t prop, int64_t *value)
{
    mz_stream_split *split = (mz_stream_split *)stream;
    switch (prop)
    {
    case MZ_STREAM_PROP_TOTAL_OUT:
        *value = split->total_out;
        break;
    case MZ_STREAM_PROP_DISK_NUMBER:
        *value = split->number_disk;
        break;
    case MZ_STREAM_PROP_DISK_SIZE:
        *value = split->disk_size;
        break;
    default:
        return MZ_EXIST_ERROR;
    }
    return MZ_OK;
}