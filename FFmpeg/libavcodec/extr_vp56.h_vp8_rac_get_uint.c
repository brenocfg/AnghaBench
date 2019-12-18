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
typedef  int /*<<< orphan*/  VP56RangeCoder ;

/* Variables and functions */
 int vp8_rac_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vp8_rac_get_uint(VP56RangeCoder *c, int bits)
{
    int value = 0;

    while (bits--) {
        value = (value << 1) | vp8_rac_get(c);
    }

    return value;
}