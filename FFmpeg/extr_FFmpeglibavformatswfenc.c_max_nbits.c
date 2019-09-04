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
 int FFABS (int) ; 

__attribute__((used)) static inline void max_nbits(int *nbits_ptr, int val)
{
    int n;

    if (val == 0)
        return;
    val = FFABS(val);
    n = 1;
    while (val != 0) {
        n++;
        val >>= 1;
    }
    if (n > *nbits_ptr)
        *nbits_ptr = n;
}