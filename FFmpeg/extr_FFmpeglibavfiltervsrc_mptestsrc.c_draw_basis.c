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
 int /*<<< orphan*/  idct (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void draw_basis(uint8_t *dst, int dst_linesize, int amp, int freq, int dc)
{
    int src[64];

    memset(src, 0, 64*sizeof(int));
    src[0] = dc;
    if (amp)
        src[freq] = amp;
    idct(dst, dst_linesize, src);
}