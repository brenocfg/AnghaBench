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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 scalar_t__ AMF_DATA_TYPE_NUMBER ; 
 int AVERROR_INVALIDDATA ; 
 double av_int2double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_get_be64 (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 

int ff_amf_read_number(GetByteContext *bc, double *val)
{
    uint64_t read;
    if (bytestream2_get_byte(bc) != AMF_DATA_TYPE_NUMBER)
        return AVERROR_INVALIDDATA;
    read = bytestream2_get_be64(bc);
    *val = av_int2double(read);
    return 0;
}