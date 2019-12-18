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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  int INT32 ;
typedef  int INT16 ;

/* Variables and functions */

INT32 Convert_8S_ToBT_NoFilter (void *pSrc, void *pDst, UINT32 dwSrcSamples, UINT32 dwSrcSps)
{
    INT32             CurrentPos;
    UINT8            *pbSrc = (UINT8 *)pSrc;
    INT16           *psDst = (INT16 *)pDst;
    INT16           sWorker, sWorker2;

    //      start at dwSpsSrc / 2, decrement by 8000
    //
    CurrentPos = (dwSrcSps >> 1);

    while (dwSrcSamples--) {
        CurrentPos -= 8000;

        if (CurrentPos >= 0) {
            pbSrc += 2;
        } else {
            sWorker = *(unsigned char *)pbSrc;
            sWorker -= 0x80;
            sWorker <<= 8;
            pbSrc++;

            sWorker2 = *(unsigned char *)pbSrc;
            sWorker2 -= 0x80;
            sWorker2 <<= 8;
            pbSrc++;

            sWorker += sWorker2;
            sWorker >>= 1;

            *psDst++ = sWorker;

            CurrentPos += dwSrcSps;
        }
    }

    return (psDst - (INT16 *)pDst);
}