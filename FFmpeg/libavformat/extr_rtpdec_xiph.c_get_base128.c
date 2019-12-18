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

__attribute__((used)) static int get_base128(const uint8_t ** buf, const uint8_t * buf_end)
{
    int n = 0;
    for (; *buf < buf_end; ++*buf) {
        n <<= 7;
        n += **buf & 0x7f;
        if (!(**buf & 0x80)) {
            ++*buf;
            return n;
        }
    }
    return 0;
}