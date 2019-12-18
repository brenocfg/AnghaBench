#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double const freq; } ;
typedef  TYPE_1__ GainEntry ;

/* Variables and functions */

__attribute__((used)) static int gain_entry_compare(const void *key, const void *memb)
{
    const double *freq = key;
    const GainEntry *entry = memb;

    if (*freq < entry[0].freq)
        return -1;
    if (*freq > entry[1].freq)
        return 1;
    return 0;
}