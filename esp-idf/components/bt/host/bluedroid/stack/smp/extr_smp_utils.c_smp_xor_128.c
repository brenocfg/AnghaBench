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
typedef  size_t UINT8 ;
typedef  size_t* BT_OCTET16 ;

/* Variables and functions */
 size_t BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 

void smp_xor_128(BT_OCTET16 a, const BT_OCTET16 b)
{
    UINT8 i, *aa = a;
    const UINT8 *bb = b;

    SMP_TRACE_EVENT("smp_xor_128\n");
    for (i = 0; i < BT_OCTET16_LEN; i++) {
        aa[i] = aa[i] ^ bb[i];
    }
}