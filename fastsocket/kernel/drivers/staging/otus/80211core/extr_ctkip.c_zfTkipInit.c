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
typedef  void* u32_t ;
typedef  int u16_t ;
struct zsTkipSeed {int iv16; void* iv32; int /*<<< orphan*/  tk; int /*<<< orphan*/  ta; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  zfTkipPhase1KeyMix (void*,struct zsTkipSeed*) ; 
 int /*<<< orphan*/  zfZeroMemory (int*,int) ; 

void zfTkipInit(u8_t* key, u8_t* ta, struct zsTkipSeed* pSeed, u8_t* initIv)
{
    u16_t  iv16;
    u32_t  iv32;
    u16_t  i;

    /* clear memory */
    zfZeroMemory((u8_t*) pSeed, sizeof(struct zsTkipSeed));
    /* set key to seed */
    zfMemoryCopy(pSeed->ta, ta, 6);
    zfMemoryCopy(pSeed->tk, key, 16);

    iv16 = *initIv++;
    iv16 += *initIv<<8;
    initIv++;

    iv32=0;

    for(i=0; i<4; i++)      // initiv is little endian
    {
        iv32 += *initIv<<(i*8);
        *initIv++;
    }

    pSeed->iv32 = iv32+1; // Force Recalculating on Tkip Phase1
    zfTkipPhase1KeyMix(iv32, pSeed);

    pSeed->iv16 = iv16;
    pSeed->iv32 = iv32;
}