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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  endian_swap_rate (int*) ; 
 int /*<<< orphan*/  mem_cpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  permute (int*) ; 
 int /*<<< orphan*/  squeeze_permute (int*,unsigned char*) ; 
 int /*<<< orphan*/  xor128 (int*,unsigned char const*) ; 

void uc_hash(uint32_t st[12], unsigned char h[32], const unsigned char *msg, size_t len)
{
    unsigned char padded[16 + 1];
    size_t        off = 0;
    size_t        leftover;

    if (len > 16) {
        for (; off < len - 16; off += 16) {
            endian_swap_rate(st);
            xor128(st, &msg[off]);
            endian_swap_rate(st);
            permute(st);
        }
    }
    leftover = len - off;
    memset(padded, 0, 16);
    mem_cpy(padded, &msg[off], leftover);
    padded[leftover] = 0x80;
    endian_swap_rate(st);
    xor128(st, padded);
    endian_swap_rate(st);
    st[11] ^= (1UL << 24 | (uint32_t) leftover >> 4 << 25);
    permute(st);
    squeeze_permute(st, &h[0]);
    squeeze_permute(st, &h[16]);
}