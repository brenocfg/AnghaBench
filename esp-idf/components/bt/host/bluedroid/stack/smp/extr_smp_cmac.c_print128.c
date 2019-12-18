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
typedef  int UINT8 ;
typedef  scalar_t__ BT_OCTET16 ;

/* Variables and functions */
 int BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_TRACE_WARNING (char*,...) ; 

void print128(BT_OCTET16 x, const UINT8 *key_name)
{
#if SMP_DEBUG == TRUE && SMP_DEBUG_VERBOSE == TRUE
    UINT8  *p = (UINT8 *)x;
    UINT8  i;

    SMP_TRACE_WARNING("%s(MSB ~ LSB) = ", key_name);

    for (i = 0; i < 4; i ++) {
        SMP_TRACE_WARNING("%02x %02x %02x %02x",
                          p[BT_OCTET16_LEN - i * 4 - 1], p[BT_OCTET16_LEN - i * 4 - 2],
                          p[BT_OCTET16_LEN - i * 4 - 3], p[BT_OCTET16_LEN - i * 4 - 4]);
    }
#endif
}