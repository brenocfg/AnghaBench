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
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 size_t BTM_EIR_MAX_SERVICES ; 
 scalar_t__* BTM_EIR_UUID_LKUP_TBL ; 

__attribute__((used)) static UINT8 btm_convert_uuid_to_eir_service( UINT16 uuid16 )
{
    UINT8 xx;

    for ( xx = 0; xx < BTM_EIR_MAX_SERVICES; xx++ ) {
        if ( uuid16 == BTM_EIR_UUID_LKUP_TBL[xx]) {
            return xx;
        }
    }
    return BTM_EIR_MAX_SERVICES;
}