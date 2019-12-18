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

/* Variables and functions */

__attribute__((used)) static inline int equals(const unsigned char a[16], const unsigned char b[16], size_t len)
{
    unsigned char d = 0;
    size_t        i;

    for (i = 0; i < len; i++) {
        d |= a[i] ^ b[i];
    }
    return 1 & ((d - 1) >> 8);
}