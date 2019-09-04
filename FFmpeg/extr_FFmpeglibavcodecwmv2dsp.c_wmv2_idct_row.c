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

/* Variables and functions */
 short W0 ; 
 short W1 ; 
 short W2 ; 
 short W3 ; 
 short W5 ; 
 short W6 ; 
 short W7 ; 

__attribute__((used)) static void wmv2_idct_row(short * b)
{
    int s1, s2;
    int a0, a1, a2, a3, a4, a5, a6, a7;

    /* step 1 */
    a1 = W1 * b[1] + W7 * b[7];
    a7 = W7 * b[1] - W1 * b[7];
    a5 = W5 * b[5] + W3 * b[3];
    a3 = W3 * b[5] - W5 * b[3];
    a2 = W2 * b[2] + W6 * b[6];
    a6 = W6 * b[2] - W2 * b[6];
    a0 = W0 * b[0] + W0 * b[4];
    a4 = W0 * b[0] - W0 * b[4];

    /* step 2 */
    s1 = (int)(181U * (a1 - a5 + a7 - a3) + 128) >> 8; // 1, 3, 5, 7
    s2 = (int)(181U * (a1 - a5 - a7 + a3) + 128) >> 8;

    /* step 3 */
    b[0] = (a0 + a2 + a1 + a5 + (1 << 7)) >> 8;
    b[1] = (a4 + a6 + s1      + (1 << 7)) >> 8;
    b[2] = (a4 - a6 + s2      + (1 << 7)) >> 8;
    b[3] = (a0 - a2 + a7 + a3 + (1 << 7)) >> 8;
    b[4] = (a0 - a2 - a7 - a3 + (1 << 7)) >> 8;
    b[5] = (a4 - a6 - s2      + (1 << 7)) >> 8;
    b[6] = (a4 + a6 - s1      + (1 << 7)) >> 8;
    b[7] = (a0 + a2 - a1 - a5 + (1 << 7)) >> 8;
}