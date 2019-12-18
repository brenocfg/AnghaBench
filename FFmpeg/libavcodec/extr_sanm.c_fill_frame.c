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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_memcpy_backptr (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void fill_frame(uint16_t *pbuf, int buf_size, uint16_t color)
{
    if (buf_size--) {
        *pbuf++ = color;
        av_memcpy_backptr((uint8_t*)pbuf, 2, 2*buf_size);
    }
}