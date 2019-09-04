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

__attribute__((used)) static inline int decode_e (unsigned e,
                            unsigned s,
                            unsigned n)
{
    /* result is encoded number of units - 2
     * (for use as zero based index)
     * or -1 if invalid
     */
    unsigned char E = ((e * n * 2 + 1) / s - 3) / 2;
    return((E >= n - 3) ? -1 : E);
}