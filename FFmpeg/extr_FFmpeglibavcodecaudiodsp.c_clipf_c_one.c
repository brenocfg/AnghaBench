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
typedef  unsigned int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t clipf_c_one(uint32_t a, uint32_t mini,
                                   uint32_t maxi, uint32_t maxisign)
{
    if (a > mini)
        return mini;
    else if ((a ^ (1U << 31)) > maxisign)
        return maxi;
    else
        return a;
}