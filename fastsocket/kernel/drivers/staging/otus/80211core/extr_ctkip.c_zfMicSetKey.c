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
struct zsMicVar {void* k1; void* k0; } ;

/* Variables and functions */
 void* zfGetU32t (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfMicClear (struct zsMicVar*) ; 

void zfMicSetKey(u8_t* key, struct zsMicVar* pMic)
{
    pMic->k0 = zfGetU32t(key);
    pMic->k1 = zfGetU32t(key+4);
    zfMicClear(pMic);
}