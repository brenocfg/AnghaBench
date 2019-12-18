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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ pow_2 (scalar_t__ const) ; 

__attribute__((used)) static uint64_t sse_line_16bit(const uint8_t *_main_line, const uint8_t *_ref_line, int outw)
{
    int j;
    uint64_t m2 = 0;
    const uint16_t *main_line = (const uint16_t *) _main_line;
    const uint16_t *ref_line = (const uint16_t *) _ref_line;

    for (j = 0; j < outw; j++)
        m2 += pow_2(main_line[j] - ref_line[j]);

    return m2;
}