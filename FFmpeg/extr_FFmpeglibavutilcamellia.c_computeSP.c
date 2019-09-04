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
typedef  int uint64_t ;

/* Variables and functions */
 int* SBOX1 ; 
 int* SBOX2 ; 
 int* SBOX3 ; 
 int* SBOX4 ; 
 int** SP ; 

__attribute__((used)) static void computeSP(void)
{
    uint64_t z;
    int i;
    for (i = 0; i < 256; i++) {
        z = SBOX1[i];
        SP[0][i] = (z << 56) ^ (z << 48) ^ (z << 40) ^ (z << 24) ^ z;
        SP[7][i] = (z << 56) ^ (z << 48) ^ (z << 40) ^ (z << 24) ^ (z << 16) ^ (z << 8);
        z = SBOX2[i];
        SP[1][i] = (z << 48) ^ (z << 40) ^ (z << 32) ^ (z << 24) ^ (z << 16);
        SP[4][i] = (z << 48) ^ (z << 40) ^ (z << 32) ^ (z << 16) ^ (z << 8) ^ z;
        z = SBOX3[i];
        SP[2][i] = (z << 56) ^ (z << 40) ^ (z << 32) ^ (z << 16) ^ (z << 8);
        SP[5][i] = (z << 56) ^ (z << 40) ^ (z << 32) ^ (z << 24) ^ (z << 8) ^ z;
        z = SBOX4[i];
        SP[3][i] = (z << 56) ^ (z << 48) ^ (z << 32) ^ (z << 8) ^ z;
        SP[6][i] = (z << 56) ^ (z << 48) ^ (z << 32) ^ (z << 24) ^ (z << 16) ^ z;
    }
}