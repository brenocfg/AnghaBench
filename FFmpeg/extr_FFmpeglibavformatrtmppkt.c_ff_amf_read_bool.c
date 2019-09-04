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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AMF_DATA_TYPE_BOOL ; 
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 

int ff_amf_read_bool(GetByteContext *bc, int *val)
{
    if (bytestream2_get_byte(bc) != AMF_DATA_TYPE_BOOL)
        return AVERROR_INVALIDDATA;
    *val = bytestream2_get_byte(bc);
    return 0;
}