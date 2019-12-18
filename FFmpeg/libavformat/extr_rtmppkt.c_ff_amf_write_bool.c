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
 int AMF_DATA_TYPE_BOOL ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,int) ; 

void ff_amf_write_bool(uint8_t **dst, int val)
{
    bytestream_put_byte(dst, AMF_DATA_TYPE_BOOL);
    bytestream_put_byte(dst, val);
}