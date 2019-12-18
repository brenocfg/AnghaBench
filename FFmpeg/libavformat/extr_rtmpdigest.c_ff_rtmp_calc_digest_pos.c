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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

int ff_rtmp_calc_digest_pos(const uint8_t *buf, int off, int mod_val,
                            int add_val)
{
    int i, digest_pos = 0;

    for (i = 0; i < 4; i++)
        digest_pos += buf[i + off];
    digest_pos = digest_pos % mod_val + add_val;

    return digest_pos;
}