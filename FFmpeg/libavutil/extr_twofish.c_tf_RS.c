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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL32 (int*) ; 
 int /*<<< orphan*/  AV_WL32 (int*,int /*<<< orphan*/ ) ; 
 int gfmul (int,int) ; 

__attribute__((used)) static uint32_t tf_RS(uint32_t k0, uint32_t k1)
{
    uint8_t s[4], m[8];
    AV_WL32(m, k0);
    AV_WL32(m + 4, k1);
    s[0] = gfmul(0x01, m[0]) ^ gfmul(0xa4, m[1]) ^ gfmul(0x55, m[2]) ^ gfmul(0x87, m[3]) ^ gfmul(0x5a, m[4]) ^ gfmul(0x58, m[5]) ^ gfmul(0xdb, m[6]) ^ gfmul(0x9e, m[7]);
    s[1] = gfmul(0xa4, m[0]) ^ gfmul(0x56, m[1]) ^ gfmul(0x82, m[2]) ^ gfmul(0xf3, m[3]) ^ gfmul(0x1e, m[4]) ^ gfmul(0xc6, m[5]) ^ gfmul(0x68, m[6]) ^ gfmul(0xe5, m[7]);
    s[2] = gfmul(0x02, m[0]) ^ gfmul(0xa1, m[1]) ^ gfmul(0xfc, m[2]) ^ gfmul(0xc1, m[3]) ^ gfmul(0x47, m[4]) ^ gfmul(0xae, m[5]) ^ gfmul(0x3d, m[6]) ^ gfmul(0x19, m[7]);
    s[3] = gfmul(0xa4, m[0]) ^ gfmul(0x55, m[1]) ^ gfmul(0x87, m[2]) ^ gfmul(0x5a, m[3]) ^ gfmul(0x58, m[4]) ^ gfmul(0xdb, m[5]) ^ gfmul(0x9e, m[6]) ^ gfmul(0x03, m[7]);
    return AV_RL32(s);
}