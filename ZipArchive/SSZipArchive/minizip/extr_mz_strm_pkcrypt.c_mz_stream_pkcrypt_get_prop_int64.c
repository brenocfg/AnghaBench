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
struct TYPE_2__ {int /*<<< orphan*/  max_total_in; int /*<<< orphan*/  total_out; int /*<<< orphan*/  total_in; } ;
typedef  TYPE_1__ mz_stream_pkcrypt ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_EXIST_ERROR ; 
 int MZ_OK ; 
 int /*<<< orphan*/  MZ_PKCRYPT_HEADER_SIZE ; 
#define  MZ_STREAM_PROP_FOOTER_SIZE 132 
#define  MZ_STREAM_PROP_HEADER_SIZE 131 
#define  MZ_STREAM_PROP_TOTAL_IN 130 
#define  MZ_STREAM_PROP_TOTAL_IN_MAX 129 
#define  MZ_STREAM_PROP_TOTAL_OUT 128 

int32_t mz_stream_pkcrypt_get_prop_int64(void *stream, int32_t prop, int64_t *value)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;
    switch (prop)
    {
    case MZ_STREAM_PROP_TOTAL_IN:
        *value = pkcrypt->total_in;
        break;
    case MZ_STREAM_PROP_TOTAL_OUT:
        *value = pkcrypt->total_out;
        break;
    case MZ_STREAM_PROP_TOTAL_IN_MAX:
        *value = pkcrypt->max_total_in;
        break;
    case MZ_STREAM_PROP_HEADER_SIZE:
        *value = MZ_PKCRYPT_HEADER_SIZE;
        break;
    case MZ_STREAM_PROP_FOOTER_SIZE:
        *value = 0;
        break;
    default:
        return MZ_EXIST_ERROR;
    }
    return MZ_OK;
}