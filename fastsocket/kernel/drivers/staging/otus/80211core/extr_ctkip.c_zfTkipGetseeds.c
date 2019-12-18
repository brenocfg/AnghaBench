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
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsTkipSeed {int* ppk; int /*<<< orphan*/ * tk; } ;

/* Variables and functions */
 int ZM_BYTE_TO_WORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ZM_HI8 (int /*<<< orphan*/ ) ; 
 int ZM_LO8 (int /*<<< orphan*/ ) ; 

void zfTkipGetseeds(u16_t iv16, u8_t *RC4Key, struct zsTkipSeed *Seed)
{
    RC4Key[0]  = ZM_HI8(iv16);
    RC4Key[1]  = (ZM_HI8(iv16) | 0x20) & 0x7f;
    RC4Key[2]  = ZM_LO8(iv16);
    RC4Key[3]  = ((Seed->ppk[5] ^ ZM_BYTE_TO_WORD(Seed->tk[1],Seed->tk[0]))>>1) & 0xff;
    RC4Key[4]  = Seed->ppk[0] & 0xff;
    RC4Key[5]  = Seed->ppk[0] >> 8;
    RC4Key[6]  = Seed->ppk[1] & 0xff;
    RC4Key[7]  = Seed->ppk[1] >> 8;
    RC4Key[8]  = Seed->ppk[2] & 0xff;
    RC4Key[9]  = Seed->ppk[2] >> 8;
    RC4Key[10] = Seed->ppk[3] & 0xff;
    RC4Key[11] = Seed->ppk[3] >> 8;
    RC4Key[12] = Seed->ppk[4] & 0xff;
    RC4Key[13] = Seed->ppk[4] >> 8;
    RC4Key[14] = Seed->ppk[5] & 0xff;
    RC4Key[15] = Seed->ppk[5] >> 8;
}