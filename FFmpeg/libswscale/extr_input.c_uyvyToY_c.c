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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static void uyvyToY_c(uint8_t *dst, const uint8_t *src, const uint8_t *unused1, const uint8_t *unused2,  int width,
                      uint32_t *unused)
{
    int i;
    for (i = 0; i < width; i++)
        dst[i] = src[2 * i + 1];
}