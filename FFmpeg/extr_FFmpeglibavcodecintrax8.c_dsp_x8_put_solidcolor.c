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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void dsp_x8_put_solidcolor(const uint8_t pix, uint8_t *dst,
                                  const ptrdiff_t linesize)
{
    int k;
    for (k = 0; k < 8; k++) {
        memset(dst, pix, 8);
        dst += linesize;
    }
}