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

__attribute__((used)) static inline void
decode10 (unsigned char *buf,
          unsigned long n,
          int i)
{
    buf += i;
    while(--i >= 0) {
        unsigned char d = n % 10;
        n /= 10;
        *--buf = '0' + d;
    }
}