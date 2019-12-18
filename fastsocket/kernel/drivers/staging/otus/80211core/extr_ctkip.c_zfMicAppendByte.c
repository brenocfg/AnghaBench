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
struct zsMicVar {int m; int nBytes; int left; int right; } ;

/* Variables and functions */
 int ZM_ROL32 (int,int) ; 
 int ZM_ROR32 (int,int) ; 

void zfMicAppendByte(u8_t b, struct zsMicVar* pMic)
{
    // Append the byte to our word-sized buffer
    pMic->m |= b << (8* pMic->nBytes);
    pMic->nBytes++;

    // Process the word if it is full.
    if ( pMic->nBytes >= 4 )
    {
        pMic->left ^= pMic->m;
        pMic->right ^= ZM_ROL32(pMic->left, 17 );
        pMic->left += pMic->right;
        pMic->right ^= ((pMic->left & 0xff00ff00) >> 8) |
                       ((pMic->left & 0x00ff00ff) << 8);
        pMic->left += pMic->right;
        pMic->right ^= ZM_ROL32( pMic->left, 3 );
        pMic->left += pMic->right;
        pMic->right ^= ZM_ROR32( pMic->left, 2 );
        pMic->left += pMic->right;
        // Clear the buffer
        pMic->m = 0;
        pMic->nBytes = 0;
    }
}