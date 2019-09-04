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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 scalar_t__ AMF_DATA_TYPE_STRING ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int ff_amf_get_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

int ff_amf_read_string(GetByteContext *bc, uint8_t *str,
                       int strsize, int *length)
{
    if (bytestream2_get_byte(bc) != AMF_DATA_TYPE_STRING)
        return AVERROR_INVALIDDATA;
    return ff_amf_get_string(bc, str, strsize, length);
}