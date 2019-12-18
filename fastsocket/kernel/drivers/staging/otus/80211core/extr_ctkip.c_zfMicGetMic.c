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
typedef  int /*<<< orphan*/  u8_t ;
struct zsMicVar {scalar_t__ nBytes; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfMicAppendByte (int,struct zsMicVar*) ; 
 int /*<<< orphan*/  zfMicClear (struct zsMicVar*) ; 
 int /*<<< orphan*/  zfPutU32t (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zfMicGetMic(u8_t* dst, struct zsMicVar* pMic)
{
    // Append the minimum padding
    zfMicAppendByte(0x5a, pMic);
    zfMicAppendByte(0, pMic);
    zfMicAppendByte(0, pMic);
    zfMicAppendByte(0, pMic);
    zfMicAppendByte(0, pMic);

    // and then zeroes until the length is a multiple of 4
    while( pMic->nBytes != 0 )
    {
        zfMicAppendByte(0, pMic);
    }

    // The appendByte function has already computed the result.
    zfPutU32t(dst, pMic->left);
    zfPutU32t(dst+4, pMic->right);

    // Reset to the empty message.
    zfMicClear(pMic);

}