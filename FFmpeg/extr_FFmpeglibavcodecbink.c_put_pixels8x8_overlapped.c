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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void put_pixels8x8_overlapped(uint8_t *dst, uint8_t *src, int stride)
{
    uint8_t tmp[64];
    int i;
    for (i = 0; i < 8; i++)
        memcpy(tmp + i*8, src + i*stride, 8);
    for (i = 0; i < 8; i++)
        memcpy(dst + i*stride, tmp + i*8, 8);
}