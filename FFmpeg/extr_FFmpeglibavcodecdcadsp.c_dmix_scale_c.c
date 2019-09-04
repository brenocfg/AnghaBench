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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mul15 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dmix_scale_c(int32_t *dst, int scale, ptrdiff_t len)
{
    int i;

    for (i = 0; i < len; i++)
        dst[i] = mul15(dst[i], scale);
}