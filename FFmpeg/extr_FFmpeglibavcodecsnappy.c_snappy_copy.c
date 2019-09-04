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

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 

__attribute__((used)) static int snappy_copy(uint8_t *start, uint8_t *p, int size,
                       unsigned int off, int len)
{
    uint8_t *q;
    int i;
    if (off > p - start || size < len)
        return AVERROR_INVALIDDATA;

    q = p - off;

    for (i = 0; i < len; i++)
        p[i] = q[i];

    return len;
}