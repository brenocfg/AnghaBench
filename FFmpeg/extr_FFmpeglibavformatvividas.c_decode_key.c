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
 unsigned int* keybits ; 

__attribute__((used)) static uint32_t decode_key(uint8_t *buf)
{
    uint32_t key = 0;

    for (int i = 0; i < 32; i++) {
        unsigned p = keybits[i];
        key |= !!(buf[p>>3] & (1<<(p&7))) << i;
    }

    return key;
}