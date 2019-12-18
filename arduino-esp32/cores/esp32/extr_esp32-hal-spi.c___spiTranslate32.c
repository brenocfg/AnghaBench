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

__attribute__((used)) static uint32_t __spiTranslate32(uint32_t data)
{
    union {
        uint32_t l;
        uint8_t b[4];
    } out;
    out.l = data;
    return out.b[3] | (out.b[2] << 8) | (out.b[1] << 16) | (out.b[0] << 24);
}