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

/* Variables and functions */
 scalar_t__ BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 

void smp_mask_enc_key(UINT8 loc_enc_size, UINT8 *p_data)
{
    SMP_TRACE_EVENT("smp_mask_enc_key\n");
    if (loc_enc_size < BT_OCTET16_LEN) {
        for (; loc_enc_size < BT_OCTET16_LEN; loc_enc_size ++) {
            * (p_data + loc_enc_size) = 0;
        }
    }
    return;
}