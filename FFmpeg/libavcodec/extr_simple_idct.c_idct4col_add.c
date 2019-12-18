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
 int C1 ; 
 int C2 ; 
 int C3 ; 
 int C_SHIFT ; 
 scalar_t__ av_clip_uint8 (scalar_t__) ; 

__attribute__((used)) static inline void idct4col_add(uint8_t *dest, ptrdiff_t line_size, const int16_t *col)
{
    int c0, c1, c2, c3, a0, a1, a2, a3;

    a0 = col[8*0];
    a1 = col[8*1];
    a2 = col[8*2];
    a3 = col[8*3];
    c0 = (a0 + a2)*C3 + (1 << (C_SHIFT - 1));
    c2 = (a0 - a2)*C3 + (1 << (C_SHIFT - 1));
    c1 = a1 * C1 + a3 * C2;
    c3 = a1 * C2 - a3 * C1;
    dest[0] = av_clip_uint8(dest[0] + ((c0 + c1) >> C_SHIFT));
    dest += line_size;
    dest[0] = av_clip_uint8(dest[0] + ((c2 + c3) >> C_SHIFT));
    dest += line_size;
    dest[0] = av_clip_uint8(dest[0] + ((c2 - c3) >> C_SHIFT));
    dest += line_size;
    dest[0] = av_clip_uint8(dest[0] + ((c0 - c1) >> C_SHIFT));
}