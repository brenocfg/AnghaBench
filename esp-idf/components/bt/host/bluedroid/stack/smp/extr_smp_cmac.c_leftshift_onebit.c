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

/* Variables and functions */
 size_t BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 

__attribute__((used)) static void leftshift_onebit(UINT8 *input, UINT8 *output)
{
    UINT8   i, overflow = 0 , next_overflow = 0;
    SMP_TRACE_EVENT ("leftshift_onebit ");
    /* input[0] is LSB */
    for ( i = 0; i < BT_OCTET16_LEN ; i ++ ) {
        next_overflow = (input[i] & 0x80) ? 1 : 0;
        output[i] = (input[i] << 1) | overflow;
        overflow = next_overflow;
    }
    return;
}