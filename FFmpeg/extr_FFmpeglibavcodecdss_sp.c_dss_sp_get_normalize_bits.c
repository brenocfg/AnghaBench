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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 unsigned int FFABS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dss_sp_get_normalize_bits(int32_t *vector_buf, int16_t size)
{
    unsigned int val;
    int max_val;
    int i;

    val = 1;
    for (i = 0; i < size; i++)
        val |= FFABS(vector_buf[i]);

    for (max_val = 0; val <= 0x4000; ++max_val)
        val *= 2;
    return max_val;
}