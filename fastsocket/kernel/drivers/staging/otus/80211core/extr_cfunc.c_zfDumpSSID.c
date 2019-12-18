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
typedef  int u8_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 

void zfDumpSSID(u8_t length, u8_t *value)
{
    u8_t buf[50];
    u8_t tmpLength = length;

    if ( tmpLength > 49 )
    {
        tmpLength = 49;
    }

    zfMemoryCopy(buf, value, tmpLength);
    buf[tmpLength] = '\0';
    //printk("SSID: %s\n", buf);
    //zm_debug_msg_s("ssid = ", value);
}