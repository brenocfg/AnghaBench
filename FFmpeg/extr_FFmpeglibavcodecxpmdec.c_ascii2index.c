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

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ const MAX_ELEMENT ; 
 scalar_t__ const MIN_ELEMENT ; 
 int NB_ELEMENTS ; 

__attribute__((used)) static int ascii2index(const uint8_t *cpixel, int cpp)
{
    const uint8_t *p = cpixel;
    int n = 0, m = 1, i;

    for (i = 0; i < cpp; i++) {
        if (*p < MIN_ELEMENT || *p > MAX_ELEMENT)
            return AVERROR_INVALIDDATA;
        n += (*p++ - MIN_ELEMENT) * m;
        m *= NB_ELEMENTS;
    }
    return n;
}