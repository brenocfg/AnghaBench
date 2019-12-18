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
typedef  int u16_t ;
struct zsTkipSeed {int* ppk; int* ttak; int iv16; int iv16tmp; int /*<<< orphan*/ * tk; } ;

/* Variables and functions */
 int ZM_BYTE_TO_WORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* zfTkipSbox (int) ; 
 void* zfrotr1 (int) ; 

u8_t zfTkipPhase2KeyMix(u16_t iv16, struct zsTkipSeed* pSeed)
{
    u16_t tsc2;

    tsc2 = iv16;

    /* Phase 2, Step 1 */
    pSeed->ppk[0] = pSeed->ttak[0];
    pSeed->ppk[1] = pSeed->ttak[1];
    pSeed->ppk[2] = pSeed->ttak[2];
    pSeed->ppk[3] = pSeed->ttak[3];
    pSeed->ppk[4] = pSeed->ttak[4];
    pSeed->ppk[5] = (pSeed->ttak[4] + tsc2) & 0xffff;

    /* Phase2, Step 2 */
    pSeed->ppk[0] = pSeed->ppk[0]
                + zfTkipSbox(pSeed->ppk[5] ^ ZM_BYTE_TO_WORD(pSeed->tk[1],pSeed->tk[0]));
    pSeed->ppk[1] = pSeed->ppk[1]
                + zfTkipSbox(pSeed->ppk[0] ^ ZM_BYTE_TO_WORD(pSeed->tk[3],pSeed->tk[2]));
    pSeed->ppk[2] = pSeed->ppk[2]
                + zfTkipSbox(pSeed->ppk[1] ^ ZM_BYTE_TO_WORD(pSeed->tk[5],pSeed->tk[4]));
    pSeed->ppk[3] = pSeed->ppk[3]
                + zfTkipSbox(pSeed->ppk[2] ^ ZM_BYTE_TO_WORD(pSeed->tk[7],pSeed->tk[6]));
    pSeed->ppk[4] = pSeed->ppk[4]
                + zfTkipSbox(pSeed->ppk[3] ^ ZM_BYTE_TO_WORD(pSeed->tk[9],pSeed->tk[8]));
    pSeed->ppk[5] = pSeed->ppk[5]
                + zfTkipSbox(pSeed->ppk[4] ^ ZM_BYTE_TO_WORD(pSeed->tk[11],pSeed->tk[10]));

    pSeed->ppk[0] = pSeed->ppk[0]
                + zfrotr1(pSeed->ppk[5] ^ ZM_BYTE_TO_WORD(pSeed->tk[13],pSeed->tk[12]));
    pSeed->ppk[1] = pSeed->ppk[1]
                + zfrotr1(pSeed->ppk[0] ^ ZM_BYTE_TO_WORD(pSeed->tk[15],pSeed->tk[14]));
    pSeed->ppk[2] = pSeed->ppk[2] + zfrotr1(pSeed->ppk[1]);
    pSeed->ppk[3] = pSeed->ppk[3] + zfrotr1(pSeed->ppk[2]);
    pSeed->ppk[4] = pSeed->ppk[4] + zfrotr1(pSeed->ppk[3]);
    pSeed->ppk[5] = pSeed->ppk[5] + zfrotr1(pSeed->ppk[4]);

    if (iv16 == 0)
    {
        if (pSeed->iv16 == 0xffff)
        {
            pSeed->iv16tmp=0;
            return 1;
        }
        else
            return 0;
    }
    else if (iv16 == (pSeed->iv16+1))
    {
        pSeed->iv16tmp = iv16;
        return 1;
    }
    else
        return 0;
}