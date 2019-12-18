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
 int* RK ; 
 int ROTR32 (int,int) ; 
 int /*<<< orphan*/  SWAP32 (int*,int,int) ; 
 int XOODOO_ROUNDS ; 

__attribute__((used)) static void permute(uint32_t st[12])
{
    uint32_t e[4], a, b, c, t, r, i;

    for (r = 0; r < XOODOO_ROUNDS; r++) {
        for (i = 0; i < 4; i++) {
            e[i] = ROTR32(st[i] ^ st[i + 4] ^ st[i + 8], 18);
            e[i] ^= ROTR32(e[i], 9);
        }
        for (i = 0; i < 12; i++) {
            st[i] ^= e[(i - 1) & 3];
        }
        SWAP32(st, 7, 4);
        SWAP32(st, 7, 5);
        SWAP32(st, 7, 6);
        st[0] ^= RK[r];
        for (i = 0; i < 4; i++) {
            a         = st[i];
            b         = st[i + 4];
            c         = ROTR32(st[i + 8], 21);
            st[i + 8] = ROTR32((b & ~a) ^ c, 24);
            st[i + 4] = ROTR32((a & ~c) ^ b, 31);
            st[i] ^= c & ~b;
        }
        SWAP32(st, 8, 10);
        SWAP32(st, 9, 11);
    }
}