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
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 size_t BTM_SEC_SERVICE_ARRAY_SIZE ; 
 size_t BTM_SEC_TRUST_ALL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN btm_sec_are_all_trusted(UINT32 p_mask[])
{
    UINT32 trusted_inx;
    for (trusted_inx = 0; trusted_inx < BTM_SEC_SERVICE_ARRAY_SIZE; trusted_inx++) {
        if (p_mask[trusted_inx] != BTM_SEC_TRUST_ALL) {
            return (FALSE);
        }
    }

    return (TRUE);
}