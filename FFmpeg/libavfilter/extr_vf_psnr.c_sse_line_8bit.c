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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 scalar_t__ pow_2 (scalar_t__ const) ; 

__attribute__((used)) static uint64_t sse_line_8bit(const uint8_t *main_line,  const uint8_t *ref_line, int outw)
{
    int j;
    unsigned m2 = 0;

    for (j = 0; j < outw; j++)
        m2 += pow_2(main_line[j] - ref_line[j]);

    return m2;
}