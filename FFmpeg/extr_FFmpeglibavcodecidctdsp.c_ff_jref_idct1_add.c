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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ av_clip_uint8 (scalar_t__) ; 

__attribute__((used)) static void ff_jref_idct1_add(uint8_t *dest, ptrdiff_t line_size, int16_t *block)
{
    dest[0] = av_clip_uint8(dest[0] + ((block[0] + 4)>>3));
}