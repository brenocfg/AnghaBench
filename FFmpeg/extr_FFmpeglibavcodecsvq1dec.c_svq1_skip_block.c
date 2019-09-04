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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void svq1_skip_block(uint8_t *current, uint8_t *previous,
                            ptrdiff_t pitch, int x, int y)
{
    uint8_t *src;
    uint8_t *dst;
    int i;

    src = &previous[x + y * pitch];
    dst = current;

    for (i = 0; i < 16; i++) {
        memcpy(dst, src, 16);
        src += pitch;
        dst += pitch;
    }
}