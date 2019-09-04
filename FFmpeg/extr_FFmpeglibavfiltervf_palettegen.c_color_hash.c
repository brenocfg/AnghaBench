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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int NBITS ; 

__attribute__((used)) static inline unsigned color_hash(uint32_t color)
{
    const uint8_t r = color >> 16 & ((1<<NBITS)-1);
    const uint8_t g = color >>  8 & ((1<<NBITS)-1);
    const uint8_t b = color       & ((1<<NBITS)-1);
    return r<<(NBITS*2) | g<<NBITS | b;
}