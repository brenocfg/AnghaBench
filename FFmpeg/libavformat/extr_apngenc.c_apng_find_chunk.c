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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ AV_RB32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint8_t *apng_find_chunk(uint32_t tag, uint8_t *buf, size_t length)
{
    size_t b;
    for (b = 0; b < length; b += AV_RB32(buf + b) + 12)
        if (AV_RB32(&buf[b + 4]) == tag)
            return &buf[b];
    return NULL;
}