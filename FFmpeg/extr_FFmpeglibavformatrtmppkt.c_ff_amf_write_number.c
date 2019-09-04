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

/* Variables and functions */
 int /*<<< orphan*/  AMF_DATA_TYPE_NUMBER ; 
 int /*<<< orphan*/  av_double2int (double) ; 
 int /*<<< orphan*/  bytestream_put_be64 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void ff_amf_write_number(uint8_t **dst, double val)
{
    bytestream_put_byte(dst, AMF_DATA_TYPE_NUMBER);
    bytestream_put_be64(dst, av_double2int(val));
}