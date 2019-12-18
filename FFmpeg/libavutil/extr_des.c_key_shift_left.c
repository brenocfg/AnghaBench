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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t key_shift_left(uint64_t CDn)
{
    uint64_t carries = (CDn >> 27) & 0x10000001;
    CDn <<= 1;
    CDn  &= ~0x10000001;
    CDn  |= carries;
    return CDn;
}