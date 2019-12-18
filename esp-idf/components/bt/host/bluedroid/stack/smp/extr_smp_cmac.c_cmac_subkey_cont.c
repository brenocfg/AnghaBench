#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* param_buf; } ;
typedef  TYPE_1__ tSMP_ENC ;
typedef  int UINT8 ;

/* Variables and functions */
 int BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  cmac_prepare_last_block (int*,int*) ; 
 int /*<<< orphan*/  const_Rb ; 
 int /*<<< orphan*/  leftshift_onebit (int*,int*) ; 
 int /*<<< orphan*/  print128 (int*,int const*) ; 
 int /*<<< orphan*/  smp_xor_128 (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmac_subkey_cont(tSMP_ENC *p)
{
    UINT8 k1[BT_OCTET16_LEN], k2[BT_OCTET16_LEN];
    UINT8 *pp = p->param_buf;
    SMP_TRACE_EVENT ("cmac_subkey_cont ");
    print128(pp, (const UINT8 *)"K1 before shift");

    /* If MSB(L) = 0, then K1 = L << 1 */
    if ( (pp[BT_OCTET16_LEN - 1] & 0x80) != 0 ) {
        /* Else K1 = ( L << 1 ) (+) Rb */
        leftshift_onebit(pp, k1);
        smp_xor_128(k1, const_Rb);
    } else {
        leftshift_onebit(pp, k1);
    }

    if ( (k1[BT_OCTET16_LEN - 1] & 0x80) != 0 ) {
        /* K2 =  (K1 << 1) (+) Rb */
        leftshift_onebit(k1, k2);
        smp_xor_128(k2, const_Rb);
    } else {
        /* If MSB(K1) = 0, then K2 = K1 << 1 */
        leftshift_onebit(k1, k2);
    }

    print128(k1, (const UINT8 *)"K1");
    print128(k2, (const UINT8 *)"K2");

    cmac_prepare_last_block (k1, k2);
}