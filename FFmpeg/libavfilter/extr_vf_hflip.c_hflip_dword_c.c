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

__attribute__((used)) static void hflip_dword_c(const uint8_t *ssrc, uint8_t *ddst, int w)
{
    const uint32_t *src = (const uint32_t *)ssrc;
    uint32_t *dst = (uint32_t *)ddst;
    int j;

    for (j = 0; j < w; j++)
        dst[j] = src[-j];
}