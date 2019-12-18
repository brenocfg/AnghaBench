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
struct TYPE_2__ {int /*<<< orphan*/  encryption_mode; scalar_t__ max_total_in; scalar_t__ total_out; scalar_t__ total_in; } ;
typedef  TYPE_1__ mz_stream_wzaes ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ MZ_AES_AUTHCODE_SIZE ; 
 scalar_t__ MZ_AES_PW_VERIFY_SIZE ; 
 scalar_t__ MZ_AES_SALT_LENGTH (scalar_t__) ; 
 int MZ_EXIST_ERROR ; 
 int MZ_OK ; 
#define  MZ_STREAM_PROP_FOOTER_SIZE 132 
#define  MZ_STREAM_PROP_HEADER_SIZE 131 
#define  MZ_STREAM_PROP_TOTAL_IN 130 
#define  MZ_STREAM_PROP_TOTAL_IN_MAX 129 
#define  MZ_STREAM_PROP_TOTAL_OUT 128 

int32_t mz_stream_wzaes_get_prop_int64(void *stream, int32_t prop, int64_t *value)
{
    mz_stream_wzaes *wzaes = (mz_stream_wzaes *)stream;
    switch (prop)
    {
    case MZ_STREAM_PROP_TOTAL_IN:
        *value = wzaes->total_in;
        break;
    case MZ_STREAM_PROP_TOTAL_OUT:
        *value = wzaes->total_out;
        break;
    case MZ_STREAM_PROP_TOTAL_IN_MAX:
        *value = wzaes->max_total_in;
        break;
    case MZ_STREAM_PROP_HEADER_SIZE:
        *value = MZ_AES_SALT_LENGTH((int64_t)wzaes->encryption_mode) + MZ_AES_PW_VERIFY_SIZE;
        break;
    case MZ_STREAM_PROP_FOOTER_SIZE:
        *value = MZ_AES_AUTHCODE_SIZE;
        break;
    default:
        return MZ_EXIST_ERROR;
    }
    return MZ_OK;
}