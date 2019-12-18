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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int check_ps_sync(const uint8_t *buf)
{
    // a legal MPEG program stream must start with a Pack header in the
    // first four bytes.
    return (buf[0] == 0x00) && (buf[1] == 0x00) &&
           (buf[2] == 0x01) && (buf[3] == 0xba);
}