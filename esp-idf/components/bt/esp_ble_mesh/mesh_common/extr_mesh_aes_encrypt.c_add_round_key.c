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

__attribute__((used)) static inline void add_round_key(uint8_t *s, const unsigned int *k)
{
    s[0] ^= (uint8_t)(k[0] >> 24); s[1] ^= (uint8_t)(k[0] >> 16);
    s[2] ^= (uint8_t)(k[0] >> 8); s[3] ^= (uint8_t)(k[0]);
    s[4] ^= (uint8_t)(k[1] >> 24); s[5] ^= (uint8_t)(k[1] >> 16);
    s[6] ^= (uint8_t)(k[1] >> 8); s[7] ^= (uint8_t)(k[1]);
    s[8] ^= (uint8_t)(k[2] >> 24); s[9] ^= (uint8_t)(k[2] >> 16);
    s[10] ^= (uint8_t)(k[2] >> 8); s[11] ^= (uint8_t)(k[2]);
    s[12] ^= (uint8_t)(k[3] >> 24); s[13] ^= (uint8_t)(k[3] >> 16);
    s[14] ^= (uint8_t)(k[3] >> 8); s[15] ^= (uint8_t)(k[3]);
}