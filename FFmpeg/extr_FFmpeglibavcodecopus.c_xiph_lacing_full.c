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
 int INT_MAX ; 

__attribute__((used)) static inline int xiph_lacing_full(const uint8_t **ptr, const uint8_t *end)
{
    int val = 0;
    int next;

    while (1) {
        if (*ptr >= end || val > INT_MAX - 254)
            return AVERROR_INVALIDDATA;
        next = *(*ptr)++;
        val += next;
        if (next < 255)
            break;
        else
            val--;
    }
    return val;
}