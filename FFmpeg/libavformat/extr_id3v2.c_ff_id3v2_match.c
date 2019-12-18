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
typedef  char uint8_t ;

/* Variables and functions */

int ff_id3v2_match(const uint8_t *buf, const char *magic)
{
    return  buf[0]         == magic[0] &&
            buf[1]         == magic[1] &&
            buf[2]         == magic[2] &&
            buf[3]         != 0xff     &&
            buf[4]         != 0xff     &&
           (buf[6] & 0x80) == 0        &&
           (buf[7] & 0x80) == 0        &&
           (buf[8] & 0x80) == 0        &&
           (buf[9] & 0x80) == 0;
}