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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__* BT_OCTET16 ;

/* Variables and functions */
 scalar_t__ BT_OCTET16_LEN ; 

__attribute__((used)) static void padding ( BT_OCTET16 dest, UINT8 length )
{
    UINT8   i, *p = dest;
    /* original last block */
    for ( i = length ; i < BT_OCTET16_LEN; i++ ) {
        p[BT_OCTET16_LEN - i - 1] = ( i == length ) ? 0x80 : 0;
    }
}