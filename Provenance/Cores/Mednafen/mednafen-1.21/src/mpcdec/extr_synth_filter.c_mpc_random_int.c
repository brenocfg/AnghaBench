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
typedef  int mpc_uint32_t ;
struct TYPE_3__ {int __r1; int __r2; } ;
typedef  TYPE_1__ mpc_decoder ;

/* Variables and functions */
 int* Parity ; 

mpc_uint32_t
mpc_random_int(mpc_decoder* p_dec)
{
#if 1
    mpc_uint32_t  t1, t2, t3, t4;

    t3   = t1 = p_dec->__r1; t4   = t2 = p_dec->__r2; // Parity calculation is done via table lookup, this is also available
    t1  &= 0xF5;             t2 >>= 25;               // on CPUs without parity, can be implemented in C and avoid unpredictable
    t1   = Parity[t1];       t2  &= 0x63;             // jumps and slow rotate through the carry flag operations.
    t1 <<= 31;               t2   = Parity[t2];

    return (p_dec->__r1 = (t3 >> 1) | t1 ) ^ (p_dec->__r2 = (t4 + t4) | t2 );
#else
    return (p_dec->__r1 = (p_dec->__r1 >> 1) | ((mpc_uint32_t) Parity[ p_dec->__r1 & 0xF5] << 31))
         ^ (p_dec->__r2 = (p_dec->__r2 << 1) |  (mpc_uint32_t) Parity[(p_dec->__r2 >> 25) & 0x63]);
#endif
}