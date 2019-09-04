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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_clz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int16_t norm_w32(int32_t a)
{
    if (a == 0) {
        return 0;
    } else if (a < 0) {
        a = ~a;
    }

    return ff_clz(a);
}